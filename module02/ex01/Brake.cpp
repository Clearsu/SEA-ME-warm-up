#include <iostream>

#include "Brake.hpp"

Brake::Brake() {}
Brake::Brake(const Brake& other) {}
Brake& Brake::operator=(const Brake& other) {
    return *this;
}
Brake::~Brake() {}

void Brake::print() {
    std::cout << "Brake part" << std::endl;
}
