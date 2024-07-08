#include <iostream>

#include "Transmission.hpp"

Transmission::Transmission() {}
Transmission::Transmission(const Transmission& other) {}
Transmission& Transmission::operator=(const Transmission& other) {
    return *this;
}
Transmission::~Transmission() {}

void Transmission::print() {
    std::cout << "Transmission part" << std::endl;
}
