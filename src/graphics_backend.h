#ifndef GRAPHICS_BACKEND_H_
#define GRAPHICS_BACKEND_H_

class GraphicsBackend {
public:
    virtual void init() = 0;
    virtual void draw() = 0;
    virtual void cleanup() = 0;

    virtual bool windowShouldClose() = 0;
};

#endif // GRAPHICS_BACKEND_H_
