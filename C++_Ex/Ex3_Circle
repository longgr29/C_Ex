#include <iostream>

const double PI {3.1415};

class Circle {
public:
    Circle(double radius) : radius(radius) {}

    double area() {
        return PI * radius * radius;
    }

    double perimeter() {
        return 2 * PI * radius;
    }

private:
    double radius;
};

int main() {
    Circle c(5);
    std::cout << "Area: " << c.area() << std::endl;
    std::cout << "Perimeter: " << c.perimeter() << std::endl;
}
