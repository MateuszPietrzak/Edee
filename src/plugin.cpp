#include "plugin.h"
#include <memory>
#include <sol/sol.hpp>

Plugin::Plugin(std::string path): path(path) {

}

void Plugin::init(std::shared_ptr<sol::state> lua) {
    env = std::make_unique<sol::environment>((*lua), sol::create, lua->globals());

    lua->script_file(path, (*env));

    onInit = std::make_shared<sol::function>(env->operator[]("OnInit"));
    onCleanup = std::make_shared<sol::function>(env->operator[]("OnCleanup"));
}
