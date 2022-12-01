#include "Fraction.h"

#include <stdexcept>

Fraction::Fraction(int numerator, int denominator) : 
    Fraction(simplify(numerator, denominator)) {
}

Fraction::Fraction(int integer) : Fraction(integer, 1) {
}

Fraction Fraction::operator+(Fraction other) const {
    int newNumerator = (numerator * other.denominator) + (other.numerator * denominator);
    int newDenominator = denominator * other.denominator;
    return Fraction(newNumerator, newDenominator);
}

Fraction Fraction::operator-(Fraction other) const {
    int newNumerator = (numerator * other.denominator) - (other.numerator * denominator);
    int newDenominator = denominator * other.denominator;
    return Fraction(newNumerator, newDenominator);
}

Fraction Fraction::operator*(Fraction other) const {
    return Fraction(numerator * other.numerator, denominator * other.denominator);
}

Fraction Fraction::operator/(Fraction other) const {
    return Fraction(numerator * other.denominator, denominator * other.numerator);
}

std::string Fraction::toString() const {
    if(denominator == 1) {
        return std::to_string(numerator);
    } else {
        return std::to_string(numerator) + "/" + std::to_string(denominator);
    }
}

Fraction::Fraction(int simplifiedNumerator, int simplifiedDenominator, void*) :
    numerator(simplifiedNumerator), denominator(simplifiedDenominator) {
    if(denominator <= 0) {
        throw std::invalid_argument("Denominator must be strictly positive!");
    }
}

Fraction Fraction::simplify(int numerator, int denominator) {
    if(denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }

    for(int i = 2; i <= denominator; i++) {
        if(isMultiple(i, numerator) && isMultiple(i, denominator)) {
            numerator /= i;
            denominator /= i;
        }
    }
    return Fraction(numerator, denominator, nullptr);
}

bool Fraction::isMultiple(int a, int b) {
    a = abs(a);
    b = abs(b);

    int x = a;
    while(x < b) {
        x += a;
    }
    return x == b;
}
