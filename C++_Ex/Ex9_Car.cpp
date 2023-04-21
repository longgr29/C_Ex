#include <iostream>
#include <string>

const double maintenanceCostPerKm {0.1};

class Car {
public:
    Car(std::string color, std::string engineModel, double kmeter)
        : color(color), engineModel(engineModel), kmeter(kmeter) {}

    double calculateMaintenanceCost() const;

    void checkMileage() const;

    void printVehicleInfo() const;

private:
    std::string color;
    std::string engineModel;
    double kmeter;
};

double Car::calculateMaintenanceCost() const {
    return kmeter * maintenanceCostPerKm;
}

void Car::checkMileage() const {
    std::cout << "Current kilometer: " << kmeter << std::endl;
}

void Car::printVehicleInfo() const {
    std::cout << "Color: " << color << std::endl;
    std::cout << "Engine model: " << engineModel << std::endl;
    std::cout << "Kilometer: " << kmeter << std::endl;
}

int main() {
    Car myCar("Red", "VF8", 50000.0);
    myCar.printVehicleInfo();
    myCar.checkMileage();
    double cost = myCar.calculateMaintenanceCost();
    std::cout << "Estimated maintenance cost: " << cost << std::endl;
    return 0;
}
