#ifndef PLUGIN_H_
#define PLUGIN_H_

#include <string>
#include <sol/sol.hpp>

class Plugin {
public:
    Plugin(std::string path);

    void init(std::shared_ptr<sol::state> lua);

    std::shared_ptr<sol::function> getOnInit() const { return onInit; };
    std::shared_ptr<sol::function> getOnCleanup() const { return onCleanup; };

private:
    std::string path;

    std::unique_ptr<sol::environment> env;
    std::shared_ptr<sol::function> onInit;
    std::shared_ptr<sol::function> onCleanup;
};

#endif // PLUGIN_H_
