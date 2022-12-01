#include "Underground.h"

#include <stdexcept>

Underground::Underground(const Grid& grid, int row, int col, Direction direction, bool down) :
    GridItem(grid, row, col, direction),
    down(down) {
}

AsciiImage Underground::getImage() const {
    if(down) {
        switch(getDirection()) {
        case Direction::NORTH:
            return {
                "       ",
                "3------0",
                "| ^  ^ |",
                "|      |"
            };
        case Direction::EAST:
            return {
                "-----0  ",
                "   > |  ",
                "   > |  ",
                "-----2  "
            };
        case Direction::SOUTH:
            return {
                "|      |",
                "| V  V |",
                "1------2",
                "        "
            };
        case Direction::WEST:
            return {
                "  3------",
                "  | <    ",
                "  | <    ",
                "  1------"
            };
        }
    } else {
        switch(getDirection()) {
        case Direction::NORTH:
            return {
                "|      |",
                "| ^  ^ |",
                "1------2",
                "        "
            };
        case Direction::EAST:
            return {
                "  3------",
                "  | >    ",
                "  | >    ",
                "  1------"
            };
            
        case Direction::SOUTH:
            return {
                "       ",
                "3------0",
                "| V  V |",
                "|      |"
            };
        case Direction::WEST:
            return {
                "-----0  ",
                "   < |  ",
                "   < |  ",
                "-----2  "
            };
        }
    }

    throw std::invalid_argument("Invalid direction!");
}
