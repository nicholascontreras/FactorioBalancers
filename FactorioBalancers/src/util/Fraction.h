#pragma once

#include <string>

class Fraction {
public:
    Fraction(int numerator, int denominator);
    Fraction(int integer);

    Fraction operator+(Fraction other) const;
    Fraction operator-(Fraction other) const;
    Fraction operator*(Fraction other) const;
    Fraction operator/(Fraction other) const;

    std::string toString() const;
private:
    const int numerator, denominator;

    Fraction(int simplifiedNumerator, int simplifiedDenominator, void*);

    static Fraction simplify(int numerator, int denominator);
    static bool isMultiple(int a, int b);
};