#include "Fraction.h"

#include <stdexcept>
#include <cmath>
#include <numeric>

const double Fraction::ROUND_AT = 1.0 / 65535;

Fraction::Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {
    simplify();
}

Fraction::Fraction(int integer) : numerator(integer), denominator(1) {
}

bool Fraction::operator==(Fraction other) const {
    return numerator == other.numerator && denominator == other.denominator;
}

bool Fraction::operator<(Fraction other) const {
    return numerator * other.denominator < other.numerator* denominator;
}

bool Fraction::operator>(Fraction other) const {
    return numerator * other.denominator > other.numerator* denominator;
}

bool Fraction::operator<=(Fraction other) const {
    return operator<(other) || operator==(other);
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

Fraction Fraction::abs() const {
    return Fraction(numerator < 0 ? -numerator : numerator, denominator);
}

std::string Fraction::toString() const {
    if(denominator == 1) {
        return std::to_string(numerator);
    } else {
        return std::to_string(numerator) + "/" + std::to_string(denominator);
    }
}

void Fraction::simplify() {
    if(denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }

    int gcd = std::gcd(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;

    int nearestInteger = (int)std::round((double)numerator / denominator);
    if(std::abs(((double)numerator / denominator) - nearestInteger) <= ROUND_AT) {
        numerator = nearestInteger;
        denominator = 1;
    }
}