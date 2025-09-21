#ifndef OPENGL_BACKEND_H_
#define OPENGL_BACKEND_H_

#include "shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include <unordered_map>
#include FT_FREETYPE_H
#include <glm/glm.hpp>

#include "../graphics_backend.h"


class OpenGLBackend : public GraphicsBackend {
public:
    OpenGLBackend();

    void init();
    void draw();
    void cleanup();

    bool windowShouldClose();
private:
    GLFWwindow* window;

    struct Character {
        unsigned int textureID;
        glm::ivec2 size;
        glm::ivec2 bearing;
        unsigned int advance;
    };
    FT_Library ft;
    FT_Face face;
    std::unordered_map<char, Character> characters;
    Shader fontShader;
    unsigned int fontVBO, fontVAO;

    void renderText(std::string text, float x, float y);
};

#endif // OPENGL_BACKEND_H_
