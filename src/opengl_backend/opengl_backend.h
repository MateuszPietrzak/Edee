#ifndef OPENGL_BACKEND_H_
#define OPENGL_BACKEND_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
};

#endif // OPENGL_BACKEND_H_
