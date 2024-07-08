#include <vector>
#include <iostream>

#include "Kia.hpp"
#include "Eliica.hpp"

int main() {
    std::vector<ACar*> carsToTestDrive;

    carsToTestDrive.push_back(new Kia());
    carsToTestDrive.push_back(new Eliica());

    for(const ACar* car: carsToTestDrive) {
        std::cout << "[---------- Part check: " << car->getName() << " ----------]" << std::endl;
        car->printParts();
        std::cout << std::endl;
        std::cout << "[---------- Test drive: " << car->getName() << " ----------]" << std::endl;
        car->drive();
        car->stop();
        std::cout << std::endl;
    }

    return 0;
}
