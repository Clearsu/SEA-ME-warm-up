#ifndef TRANSMISSION_HPP
#define TRANSMISSION_HPP

#include "IPart.hpp"

class Transmission: public IPart {
public:
    Transmission();
    Transmission(const Transmission& other);
    Transmission& operator=(const Transmission& other);
    ~Transmission();

    void print() override;
};

#endif
