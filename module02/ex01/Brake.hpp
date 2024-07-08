#ifndef BRAKE_HPP
#define BRAKE_HPP

#include "IPart.hpp"

class Brake: public IPart {
public:
    Brake();
    Brake(const Brake& other);
    Brake& operator=(const Brake& other);
    ~Brake();

    void print() override;
};

#endif
