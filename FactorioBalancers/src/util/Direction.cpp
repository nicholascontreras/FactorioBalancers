#include "Direction.h"

#include <stdexcept>

#pragma warning(suppress: 26812)
Direction::Direction(Value v) : value(v) {
}

Direction::Direction(int index) : Direction((Value)index) {
    if(index >= NUM_DIRECTIONS) {
        throw std::invalid_argument("Invalid Direction index!");
    }
}

Direction::operator int() const {
    return value;
}

Direction Direction::clockwise() const {
    if((*this) + 1 >= NUM_DIRECTIONS) {
        return 0;
    } else {
        return (*this) + 1;
    }
}

Direction Direction::counterClockwise() const {
    if(*this == 0) {
        return NUM_DIRECTIONS - 1;
    } else {
        return (*this) - 1;
    }
}

Direction Direction::reverse() const {
    return ((*this) + (NUM_DIRECTIONS / 2)) % NUM_DIRECTIONS;
}

void Direction::translate(int& row, int& col) {
    switch(*this) {
    case NORTH:
        row--;
        break;
    case EAST:
        col++;
        break;
    case SOUTH:
        row++;
        break;
    case WEST:
        col--;
        break;
    default:
        throw std::invalid_argument("Invalid Direction!");
    }
}

std::string Direction::toString() const {
    switch(*this) {
    case NORTH:
        return "NORTH";
    case EAST:
        return "EAST";
    case SOUTH:
        return "SOUTH";
    case WEST:
        return "WEST";
    default:
        throw std::invalid_argument("Invalid Direction!");
    }
}
