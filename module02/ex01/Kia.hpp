#ifndef KIA_HPP
#define KIA_HPP

#include "ACar.hpp"

class Kia: public ACar {
public:
    Kia();
    Kia(const Kia& other);
    Kia&	operator=(const Kia& other);
    ~Kia();

    void    drive() const override;
    void    stop() const override;
};

#endif
