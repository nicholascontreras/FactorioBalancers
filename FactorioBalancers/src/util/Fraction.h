#pragma once

#include <string>

class Fraction {
public:
    Fraction(int numerator, int denominator);
    Fraction(int integer);

    bool operator==(Fraction other) const;
    bool operator<(Fraction other) const;
    bool operator>(Fraction other) const;
    bool operator<=(Fraction other) const;

    Fraction operator+(Fraction other) const;
    Fraction operator-(Fraction other) const;
    Fraction operator*(Fraction other) const;
    Fraction operator/(Fraction other) const;
    Fraction abs() const;

    std::string toString() const;
private:
    static const double ROUND_AT;

    int numerator, denominator;

    void simplify();
};