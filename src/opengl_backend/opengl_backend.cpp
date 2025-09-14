#include "opengl_backend.h"

#include <GLFW/glfw3.h>
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

}

void OpenGLBackend::draw() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void OpenGLBackend::cleanup() {
    glfwTerminate();
}

bool OpenGLBackend::windowShouldClose() {
    return glfwWindowShouldClose(window);
}
