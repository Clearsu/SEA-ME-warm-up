#ifndef ACAR_HPP
#define ACAR_HPP

#include <string>
#include <exception>

#include "Engine.hpp"
#include "Wheel.hpp"
#include "Brake.hpp"
#include "Transmission.hpp"

class ACar {
private:
    std::string		name;
    Engine*			engine;
    Wheel*			wheels;
    Brake*			brakes;
    Transmission*	transmission;
    int				speed;
    int				numWheels;

public:
    ACar();
    ACar(const ACar& other);
    ACar(const std::string& name, int speed, int numWheels);
    ACar& operator=(const ACar& other);
    virtual ~ACar();

    Engine*				getEnginePtr() const;
    Wheel*				getWheelPtr() const;
    Brake*				getBrakePtr() const;
    Transmission*		getTransmissionPtr() const;
    const std::string&	getName() const;
    int					getSpeed() const;
    int					getNumWheels() const;

    void            printParts() const;
    virtual void    drive() const = 0;
    virtual void    stop() const = 0;

    class SpeedException: public std::exception {
    public:
        const char*	what() const noexcept;
    };

    class NumWheelsException: public std::exception {
    public:
        const char*	what() const noexcept;
    };
};

#endif
