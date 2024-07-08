#include <iostream>

#include "Eliica.hpp"

Eliica::Eliica(): ACar("Eliica", 230, 8) {}

Eliica::Eliica(const Eliica& other): ACar(other) {}

Eliica&	Eliica::operator=(const Eliica& other) {
    if (this != &other) {
        this->ACar::operator=(other);
    }
    return *this;
}

Eliica::~Eliica() {}

void	Eliica::drive() const {
    std::cout << this->getName() << " is now driving." << std::endl;
    std::cout << "Speed: " << this->getSpeed() << std::endl;
    std::cout << "Those " << this->getNumWheels() << " wheels look maybe too much." << std::endl;
}

void	Eliica::stop() const {
    std::cout << this->getName() << " has stopped safely." << std::endl;
}
