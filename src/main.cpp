#include "edee.h"

int main() {
    Edee app;

    app.init();
    app.run();
    app.cleanup();

    return 0;
}
