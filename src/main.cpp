#include "edee.h"
#include <memory>
#include "opengl_backend/opengl_backend.h"

int main() {
    Edee app(std::make_unique<OpenGLBackend>());

    app.init();
    app.run();
    app.cleanup();

    return 0;
}
