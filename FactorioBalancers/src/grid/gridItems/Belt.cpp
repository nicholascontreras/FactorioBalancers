#include "Belt.h"

#include <stdexcept>

Belt::Belt(const Grid& grid, int row, int col, Direction direction) : GridItem(grid, row, col, direction) {
}

AsciiImage Belt::getImage() const {
    Direction inputDirection = determineInputDirection();
    
    if(inputDirection == Direction::SOUTH) {
        switch(getDirection()) {
        case Direction::WEST:
            return {
                "2 V  V |",
                "<      |",
                "<      |",
                "-------2"
            };
        case Direction::SOUTH:
            return {
                "| V  V |",
                "|      |",
                "|      |",
                "| V  V |"
            };
        case Direction::EAST:
            return {
                "| V  V 1",
                "|      >",
                "|      >",
                "1-------"
            };
        }
    } else if(inputDirection == Direction::WEST) {
        switch(getDirection()) {
        case Direction::NORTH:
            return {
                "| ^  ^ 1",
                "|       ",
                "|       ",
                "1-------"
            };
        case Direction::SOUTH:
            return {
                "3-------",
                "|       ",
                "|       ",
                "| V  V 3"
            };
        case Direction::WEST:
            return {
                "--------",
                "<       ",
                "<       ",
                "--------"
            };
        } 
    } else if(inputDirection == Direction::NORTH) {
        switch(getDirection()) {
        case Direction::NORTH:
            return {
                "| ^  ^ |",
                "|      |",
                "|      |",
                "|      |"
            };
        case Direction::EAST:
            return {
                "3-------",
                "|      >",
                "|      >",
                "|      3"
            };
        case Direction::WEST:
            return {
                "-------0",
                "<      |",
                "<      |",
                "0      |"
            };
        }
    } else if(inputDirection == Direction::EAST) {
        switch(getDirection()) {
        case Direction::NORTH:
            return {
                "2 ^  ^ |",
                "       |",
                "       |",
                "-------2"
            };
        case Direction::EAST:
            return {
                "--------",
                "       >",
                "       >",
                "--------"
            };
        case Direction::SOUTH:
            return {
                "-------0",
                "       |",
                "       |",
                "0 V  V |"
            };
        }
    }

    throw std::logic_error("Invalid direction configuration!");
}

Direction Belt::determineInputDirection() const {

    int behindRow = getRow();
    int behindCol = getCol();
    getDirection().reverse().translate(behindRow, behindCol);

    if(grid.isGridItemAt(behindRow, behindCol)) {
        if(grid.gridItemAt(behindRow, behindCol)->getDirection() == getDirection()) {
            return getDirection();
        }
    }

    int cwRow = getRow();
    int cwCol = getCol();
    getDirection().clockwise().translate(cwRow, cwCol);
    bool cwIn = false;

    if(grid.isGridItemAt(cwRow, cwCol)) {
        if(grid.gridItemAt(cwRow, cwCol)->getDirection() == getDirection().counterClockwise()) {
            cwIn = true;
        }
    }

    int ccwRow = getRow();
    int ccwCol = getCol();
    getDirection().counterClockwise().translate(ccwRow, ccwCol);
    bool ccwIn = false;

    if(grid.isGridItemAt(ccwRow, ccwCol)) {
        if(grid.gridItemAt(ccwRow, ccwCol)->getDirection() == getDirection().clockwise()) {
            ccwIn = true;
        }
    }

    if(cwIn && ccwIn) {
        return getDirection();
    } else if(cwIn) {
        return getDirection().counterClockwise();
    } else if(ccwIn) {
        return getDirection().clockwise();
    } else {
        return getDirection();
    }
}
