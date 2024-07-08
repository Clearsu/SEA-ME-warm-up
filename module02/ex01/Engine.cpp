#include <iostream>

#include "Engine.hpp"

Engine::Engine() {}
Engine::Engine(const Engine& other) {}
Engine& Engine::operator=(const Engine& other) {
    return *this;
}
Engine::~Engine() {}

void Engine::print() {
    std::cout << "Engine part" << std::endl;
}
