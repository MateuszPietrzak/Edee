#include "opengl_backend/opengl_backend.h"
#include "edee.h"
#include <memory>

int main() {
    Edee app(std::make_unique<OpenGLBackend>());

    app.init();
    app.run();
    app.cleanup();

    return 0;
}
