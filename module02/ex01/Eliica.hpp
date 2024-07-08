#ifndef ELIICA_HPP
#define ELIICA_HPP

#include "ACar.hpp"

class Eliica: public ACar {
public:
    Eliica();
    Eliica(const Eliica& other);
    Eliica&	operator=(const Eliica& other);
    ~Eliica();

    void    drive() const override;
    void    stop() const override;
};

#endif
