#include "edee.h"
#include "plugin.h"

#include <iostream>
#include <memory>
#include <sol/sol.hpp>

Edee::Edee(): state(0) {

}

void Edee::init() {
    std::cout << "[C++] Init Edee" << std::endl;

    lua = std::make_shared<sol::state>();
    lua->open_libraries(sol::lib::base);

    sol::usertype<Edee> edeeType = lua->new_usertype<Edee>("Edee");

    edeeType["setState"] = &Edee::setState;
    edeeType["getState"] = &Edee::getState;

    plugins.push_back(std::make_unique<Plugin>("./plugins/example/plugin.lua"));

    for (auto& plugin: plugins) {
        plugin->init(lua);

        auto onInit = plugin->getOnInit();
        onInit->operator()(this);
    }
}

void Edee::run() {
    std::cout << "[C++] Run Edee" << std::endl;
}

void Edee::cleanup() {
    std::cout << "[C++] Cleanup Edee" << std::endl;
    for (auto& plugin: plugins) {
        auto onCleanup = plugin->getOnCleanup();
        onCleanup->operator()(this);
    }
}

void Edee::setState(int s) {
    state = s;
}

int Edee::getState() const {
    return state;
}
