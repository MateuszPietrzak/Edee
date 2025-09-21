#include "content_panel.h"

ContentPanel::ContentPanel(int width, int height, sol::function constructor):
    width(width),
    height(height),
    constructor(constructor) {
}

void ContentPanel::init() {
    sol::object o = constructor();
    if (o.is<sol::table>()) {
        panel = o.as<sol::table>();
    }
}

void ContentPanel::draw() {
    panel["drawHeader"](panel);
    panel["draw"](panel);
}

void ContentPanel::resize(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}
