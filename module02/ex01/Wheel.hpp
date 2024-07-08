#ifndef WHEEL_HPP
#define WHEEL_HPP

#include "IPart.hpp"

class Wheel: public IPart {
public:
    Wheel();
    Wheel(const Wheel& other);
    Wheel& operator=(const Wheel& other);
    ~Wheel();

    void print() override;
};

#endif
