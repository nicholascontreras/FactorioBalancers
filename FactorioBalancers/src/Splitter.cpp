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
        }
    }

    throw std::logic_error("Invalid direction!");
}
