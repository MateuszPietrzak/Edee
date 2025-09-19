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

void ContentPanel::resize(int, int) {

}
