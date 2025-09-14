#include "edee.h"
#include "graphics_backend.h"
#include "plugin.h"

#include <iostream>
#include <memory>
#include <sol/sol.hpp>

Edee::Edee(std::unique_ptr<GraphicsBackend> graphics) :
    state(0),
    graphics(std::move(graphics)) {

}

void Edee::init() {
    std::cout << "[C++] Init Edee" << std::endl;

    graphics->init();

    lua = std::make_shared<sol::state>();
    lua->open_libraries(sol::lib::base);

    sol::usertype<Edee> edeeType = lua->new_usertype<Edee>("Edee");

    edeeType["setState"] = &Edee::setState;
    edeeType["getState"] = &Edee::getState;

    plugins.push_back(std::make_unique<Plugin>("./plugins/example/plugin.lua"));
    plugins.push_back(std::make_unique<Plugin>("./plugins/example2/plugin.lua"));

    for (auto& plugin: plugins) {
        plugin->init(lua);

        auto onInit = plugin->getOnInit();
        if (onInit->valid())
            onInit->operator()(this);
    }
}

void Edee::run() {
    std::cout << "[C++] Run Edee" << std::endl;

    while(!graphics->windowShouldClose()) {
       graphics->draw();
    }
}

void Edee::cleanup() {
    std::cout << "[C++] Cleanup Edee" << std::endl;
    for (auto& plugin: plugins) {
        auto onCleanup = plugin->getOnCleanup();
        if (onCleanup->valid())
            onCleanup->operator()(this);
    }

    graphics->cleanup();
}

void Edee::setState(int s) {
    state = s;
}

int Edee::getState() const {
    return state;
}
