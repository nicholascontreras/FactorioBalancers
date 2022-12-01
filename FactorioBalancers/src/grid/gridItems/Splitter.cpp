#include "Splitter.h"

#include <stdexcept>

Splitter::Splitter(const Grid& grid, int row, int col, Direction direction, bool leftHalf) : 
    GridItem(grid, row, col, direction),
    leftHalf(leftHalf) {
}

AsciiImage Splitter::getImage() const {
    if(leftHalf) {
        switch(getDirection()) {
        case Direction::NORTH:
            return {
                "| ^  ^ 1",
                "|       ",
                "|  L    ",
                "|      3"
            };
        case Direction::EAST:
            return {
                "--------",
                "   L   >",
                "       >",
                "0      3"
            };
        case Direction::SOUTH:
            return {
                "2      |",
                "    L  |",
                "       |",
                "0 V  V |"
            };
        case Direction::WEST:
            return {
                "2      1",
                "<       ",
                "<   L   ",
                "--------"
            };
        }
    } else {
        switch(getDirection()) {
        case Direction::NORTH:
            return {
                "2 ^  ^ |",
                "       |",
                "    R  |",
                "0      |"
            };
        case Direction::EAST:
            return {
                "2      1",
                "       >",
                "   R   >",
                "--------"
            };
        case Direction::SOUTH:
            return {
                "|      1",
                "|  R    ",
                "|       ",
                "| V  V 3"
            };
        case Direction::WEST:
            return {
                "--------",
                "<   R   ",
                "<       ",
                "0      3"
            };
        }
    }

    throw std::logic_error("Invalid direction!");
}
