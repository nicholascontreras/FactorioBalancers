#include "ItemSink.h"

#include <stdexcept>

ItemSink::ItemSink(const Grid& grid, int row, int col) :
    GridItem(grid, row, col, Direction::EAST) {
}

AsciiImage ItemSink::getImage() const {
    switch(getDirection()) {
    case Direction::EAST:
        return {
            "-------0",
            "*      |",
            "*      |",
            "-------2"
        };
    }

    throw std::invalid_argument("Invalid direction!");
}
