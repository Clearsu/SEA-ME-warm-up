#include <iostream>

#include "Wheel.hpp"

Wheel::Wheel() {}
Wheel::Wheel(const Wheel& other) {}
Wheel& Wheel::operator=(const Wheel& other) {
    return *this;
}
Wheel::~Wheel() {}

void Wheel::print() {
    std::cout << "Wheel part" << std::endl;
}
