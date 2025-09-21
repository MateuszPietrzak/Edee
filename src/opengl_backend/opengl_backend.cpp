#include "opengl_backend.h"
#include "shader.h"

#include <GLFW/glfw3.h>
#include <freetype/freetype.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <iostream>

OpenGLBackend::OpenGLBackend() {

}

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    std::cout << "[C++] Setting viewport size to " << width << " x " << height << std::endl;
}

void OpenGLBackend::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(600, 600, "Edee", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "[C++] [OpenGL] Failed to create a GLFW window!" << std::endl;
        return;
    }

    glfwMakeContextCurrent(window);

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "[C++] [OpenGL] Failed to load GLAD!" << std::endl;
        return;
    }

    glViewport(0, 0, 600, 600);

    if (FT_Init_FreeType(&ft)) {
        std::cout << "[C++] [FreeType] Failed to init the library!" << std::endl;
        return;
    }

    if (FT_New_Face(ft, "./assets/fonts/Fira_Code_v6.2/ttf/FiraCode-Regular.ttf", 0, &face)) {
        std::cout << "[C++] [FreeType] Failed to create a face!" << std::endl;
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; c++) {
        if(FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "[C++] [FreeType] Failed to load glyph!" << std::endl;
            continue;
        }
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
                     face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
                     face->glyph->bitmap.buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<unsigned int>(face->glyph->advance.x)
        };
        characters[c] = character;
    }
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    fontShader.load("./src/opengl_backend/shaders/font_shader.vs", "./src/opengl_backend/shaders/font_shader.fs");

    glGenVertexArrays(1, &fontVAO);
    glGenBuffers(1, &fontVBO);
    glBindVertexArray(fontVAO);
    glBindBuffer(GL_ARRAY_BUFFER, fontVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    fontShader.use();
    glm::mat4 projection = glm::ortho(0.0f, 600.0f, 0.0f, 600.0f);
    fontShader.setMat4("projection", projection);
}

void OpenGLBackend::draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    renderText("Hello, world!", 25.0f, 25.0f);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void OpenGLBackend::cleanup() {
    glfwTerminate();
}

bool OpenGLBackend::windowShouldClose() {
    return glfwWindowShouldClose(window);
}

void OpenGLBackend::renderText(std::string text, float x, float y) {
    fontShader.use();
    fontShader.setVec3("textColor", glm::vec3(0.91f ,0.486f, 0.118f));
    glActiveTexture(GL_TEXTURE0);
    fontShader.setInt("text", 0);
    glBindVertexArray(fontVAO);

    for (const auto& c: text) {
        Character ch = characters[c];

        float xpos = x + ch.bearing.x;
        float ypos = y - (ch.size.y - ch.bearing.y);

        float w = ch.size.x;
        float h = ch.size.y;

        float vertices[6][4] = {
            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos, ypos, 0.0f, 1.0f},
            {xpos + w, ypos, 1.0f, 1.0f},
            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos + w, ypos, 1.0f, 1.0f},
            {xpos + w, ypos + h, 1.0f, 0.0f}
        };

        glBindTexture(GL_TEXTURE_2D, ch.textureID);

        glBindBuffer(GL_ARRAY_BUFFER, fontVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += ch.advance >> 6;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
