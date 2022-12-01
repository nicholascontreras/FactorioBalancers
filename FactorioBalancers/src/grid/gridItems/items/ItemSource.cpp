#include "ItemSource.h"

#include <stdexcept>

ItemSource::ItemSource(const Grid& grid, int row, int col) :
    GridItem(grid, row, col, Direction::EAST) {
}

AsciiImage ItemSource::getImage() const {
    switch(getDirection()) {
    case Direction::EAST:
        return {
            "3-------",
            "|      *",
            "|      *",
            "1-------"
        };
    }

    throw std::invalid_argument("Invalid direction!");
}
