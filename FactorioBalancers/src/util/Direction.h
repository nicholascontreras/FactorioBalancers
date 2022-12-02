#pragma once

#include <string>

class Direction {
public:
    enum Value { NORTH, EAST, SOUTH, WEST, NUM_DIRECTIONS };

    Direction(Value v);

    Direction(int index);
    operator int() const;

    Direction clockwise() const;
    Direction counterClockwise() const;
    Direction reverse() const;

    void translate(int& row, int& col);

    std::string toString() const;
private:
    const Value value;
};