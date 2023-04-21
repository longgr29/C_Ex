#include <iostream>
#include <string>

class Animal {
public:
    Animal(std::string name, int age, double weight) : name(name), age(age), weight(weight) {}

    double bmi() {
        return weight / (height * height);
    }

    bool is_older_than(const Animal& other) {
        return age > other.age;
    }

    bool is_heavier_than(const Animal& other) {
        return weight > other.weight;
    }

private:
    std::string name;
    int age;
    double weight;
};

int main() {
    Animal a("cat", 5, 4.5);
    Animal b("dog", 3, 6.2);

    std::cout << "Animal a is older than animal b: " << a.is_older_than(b) << std::endl;
    std::cout << "Animal a is heavier than animal b: " << a.is_heavier_than(b) << std::endl;
}
