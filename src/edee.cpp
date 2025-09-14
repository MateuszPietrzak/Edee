#include "edee.h"

#include <iostream>

Edee::Edee() {

}

void Edee::init() {
    std::cout << "Init Edee" << std::endl;
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
