#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "IPart.hpp"

class Engine: public IPart {
public:
    Engine();
    Engine(const Engine& other);
    Engine& operator=(const Engine& other);
    ~Engine();

    void print() override;
};

#endif
