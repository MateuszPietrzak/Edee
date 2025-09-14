#include "edee.h"

#include <iostream>
#include <sol/sol.hpp>

Edee::Edee(): state(0) {

}

void Edee::init() {
    std::cout << "Init Edee" << std::endl;

    sol::state lua;
    lua.open_libraries(sol::lib::base);

    sol::usertype<Edee> edeeType = lua.new_usertype<Edee>("Edee",sol::constructors<Edee()>());

    edeeType["setState"] = &Edee::setState;
    edeeType["getState"] = &Edee::getState;

    lua.script_file("./plugins/example/plugin.lua");

    sol::function onInit = lua["OnInit"];

    onInit(this);
}

void Edee::run() {
    std::cout << "Run Edee" << std::endl;
}

void Edee::cleanup() {
    std::cout << "Cleanup Edee" << std::endl;
}

void Edee::setState(int s) {
    state = s;
}

int Edee::getState() const {
    return state;
}
