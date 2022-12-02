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
    int numerator, denominator;

    void simplify();
    static bool isMultiple(int a, int b);
};