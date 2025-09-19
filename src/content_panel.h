#ifndef CONTENT_PANEL_H_
#define CONTENT_PANEL_H_

#include "panel.h"

#include <sol/sol.hpp>

class ContentPanel: public Panel {
public:
    ContentPanel(int width, int height, sol::function constructor);

    void init();
    void draw();
    void resize(int width, int height);

private:
    int width;
    int height;

    sol::function constructor;
    sol::table panel;
};

#endif // CONTENT_PANEL_H_
