#include <iostream>
#include <string>

class Person {
private:
    std::string name;
    int age;
    std::string address;
public:
    Person(std::string name, int age, std::string address) : name(name), age(age), address(address) {}

    void printInfo() {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Age: " << age << std::endl;
        std::cout << "Address: " << address << std::endl;
    }

    int calculateAge() {
        return age;
    }
};

int main() {
    Person person("John", 30, "12 Main St");
    person.printInfo();
    std::cout << "Age: " << person.calculateAge() << std::endl;

    return 0;
}
