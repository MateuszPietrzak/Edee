#ifndef EDEE_H_
#define EDEE_H_

#include "plugin.h"
#include <sol/sol.hpp>

class Edee {
public:
    Edee();

    void init();
    void run();
    void cleanup();

    void setState(int s);
    int getState() const;
private:
    int state;

    std::shared_ptr<sol::state> lua;
    std::vector<std::unique_ptr<Plugin>> plugins;
};

#endif // EDEE_H_
