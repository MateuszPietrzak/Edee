#ifndef EDEE_H_
#define EDEE_H_

#include "graphics_backend.h"
#include "panel.h"
#include "plugin.h"
#include <sol/sol.hpp>
#include <unordered_map>

class Edee {
public:
    Edee(std::unique_ptr<GraphicsBackend> graphics);

    void init();
    void run();
    void cleanup();

    // Lua API
    void registerConstructor(std::string label, sol::object o);
private:
    std::unique_ptr<Panel> rootPanel;

    std::unordered_map<std::string, sol::function> panelTypes;
    std::unique_ptr<GraphicsBackend> graphics;

    std::shared_ptr<sol::state> lua;
    std::vector<std::unique_ptr<Plugin>> plugins;
};

#endif // EDEE_H_
