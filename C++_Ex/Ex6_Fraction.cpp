#include <iostream>

class Fraction {
private:
    int numerator;
    int denominator;
    
    int getGcd(int a, int b);
    
    void simplify();
    
public:
    Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {    }
    //overloaded addition operator
    Fraction operator+(const Fraction other) const;

    Fraction operator-(const Fraction other) const;

    Fraction operator*(const Fraction other) const ;

    Fraction operator/(const Fraction other) const;

    void print();
};

int Fraction::getGcd(int a, int b) {
        if (b == 0) {
            return a;
        } else {
            return getGcd(b, a % b);
        }
    }
    
void Fraction::simplify() {
    int gcd = getGcd(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;
}

Fraction Fraction::operator+(const Fraction other) const {
    int newNumerator = numerator * other.denominator + other.numerator * denominator;
    int newDenominator = denominator * other.denominator;
    return Fraction(newNumerator, newDenominator);
}

Fraction Fraction::operator-(const Fraction other) const {
    int newNumerator = numerator * other.denominator - other.numerator * denominator;
    int newDenominator = denominator * other.denominator;
    return Fraction(newNumerator, newDenominator);
}

Fraction Fraction::operator*(const Fraction other) const {
    int newNumerator = numerator * other.numerator;
    int newDenominator = denominator * other.denominator;
    return Fraction(newNumerator, newDenominator);
}

Fraction Fraction::operator/(const Fraction other) const {
    int newNumerator = numerator * other.denominator;
    int newDenominator = denominator * other.numerator;
    return Fraction(newNumerator, newDenominator);
} 

void Fraction::print() {
    simplify();
    std::cout << numerator << "/" << denominator << std::endl;
}

int main() {
    Fraction fraction1(1, 2);
    Fraction fraction2(3, 4);

    std::cout << "Fraction 1: ";
    fraction1.print();

    std::cout << "Fraction 2: ";
    fraction2.print();

    std::cout << "Sum: ";
    (fraction1 + fraction2).print();

    std::cout << "Difference: ";
    (fraction1 - fraction2).print();

    std::cout << "Product: ";
    (fraction1 * fraction2).print();

    std::cout << "Quotient: ";
    (fraction1 / fraction2).print();

    return 0;
}
