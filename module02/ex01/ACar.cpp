#include "ACar.hpp"

ACar::ACar(): name(""), speed(0), numWheels(4) {
    this->engine = new Engine();
    this->wheels = new Wheel[4];
    this->brakes = new Brake[4];
    this->transmission = new Transmission();
}

ACar::ACar(const ACar& other): name(other.name), speed(other.speed), numWheels(other.numWheels) {
    this->engine = new Engine();
    this->wheels = new Wheel[other.numWheels];
    this->brakes = new Brake[other.numWheels];
    this->transmission = new Transmission();
}

ACar::ACar(const std::string& name, int speed, int numWheels)
    : name(name), speed(speed), numWheels(numWheels) {
    if (speed < 0 || speed > 1000) {
        throw SpeedException();
    }
    if (numWheels < 2) {
        throw NumWheelsException();
    }
    this->engine = new Engine();
    this->wheels = new Wheel[numWheels];
    this->brakes = new Brake[numWheels];
    this->transmission = new Transmission();
}

ACar& ACar::operator=(const ACar& other) {
    if (this != &other) {
        this->speed = other.speed;
        if (this->numWheels != other.numWheels) {
            delete [] this->wheels;
            delete [] this->brakes;
            this->wheels = new Wheel[other.numWheels];
            this->brakes = new Brake[other.numWheels];
            this->numWheels = other.numWheels;
        }
    }
    return *this;
}

ACar::~ACar() {
    delete this->engine;
    delete [] this->wheels;
    delete [] this->brakes;
    delete this->transmission;
}

Engine*         	ACar::getEnginePtr() const { return this->engine; }
Wheel*          	ACar::getWheelPtr() const { return this->wheels; }
Brake*          	ACar::getBrakePtr() const { return this->brakes; }
Transmission*   	ACar::getTransmissionPtr() const { return this->transmission; }
const std::string&	ACar::getName() const { return this->name; }
int             	ACar::getSpeed() const { return this->speed; }
int             	ACar::getNumWheels() const { return this->numWheels; }

void ACar::printParts() const {
    this->engine->print();
    for (int i = 0; i < this->numWheels; ++i) {
        this->wheels[i].print();
        this->brakes[i].print();
    }
    this->transmission->print();
}

const char*	ACar::SpeedException::what() const noexcept {
    return "exception: speed should be in range 0 - 1000";
}

const char*	ACar::NumWheelsException::what() const noexcept {
    return "exception: Wheels cannot be less than 2";
}
