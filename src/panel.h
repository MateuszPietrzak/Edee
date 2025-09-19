#ifndef PANEL_H_
#define PANEL_H_

class Panel {
public:
    virtual void init() = 0;
    virtual void draw() = 0;
    virtual void resize(int width, int height) = 0;
};

#endif // PANEL_H_
