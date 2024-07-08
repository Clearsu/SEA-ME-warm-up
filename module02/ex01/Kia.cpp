#include <iostream>

#include "Kia.hpp"

Kia::Kia(): ACar("Kia", 240, 4) {}

Kia::Kia(const Kia& other): ACar(other) {}

Kia&	Kia::operator=(const Kia& other) {
    if (this != &other) {
        this->ACar::operator=(other);
    }
    return *this;
}

Kia::~Kia() {}

void	Kia::drive() const {
    std::cout << this->getName() << " is now driving.\n";
    std::cout << "Speed: " << this->getSpeed() << std::endl;
    std::cout << this->getName() << " is out of control, brakes not working." << std::endl;
}

void	Kia::stop() const {
    std::cout << this->getName() << " has stopped after crashing agains a tree." << std::endl;
}
