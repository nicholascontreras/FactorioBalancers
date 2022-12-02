#include "Belt.h"

#include <Windows.h>
#include <stdexcept>

Belt::Belt(const Grid& grid, int row, int col, Direction direction) : GridObject(grid, row, col, direction) {
}

bool Belt::flowCanEnter(Direction incomingFlowDirection, bool leftLane) const {
    UNREFERENCED_PARAMETER(leftLane);
    return incomingFlowDirection != getDirection().reverse();
}

bool Belt::flowEntersLeftLane(Direction incomingFlowDirection, bool leftLane) const {
    Direction beltInputDirection = determineInputDirection();
    
    if(incomingFlowDirection == beltInputDirection) {
        return leftLane;
    } else if(incomingFlowDirection == beltInputDirection.clockwise()) {
        return true;
    } else if(incomingFlowDirection == beltInputDirection.counterClockwise()) {
        return false;
    } else {
        throw std::invalid_argument("Input is not arriving from valid Direction!");
    }
}

bool Belt::flowHasPathToSink(bool leftLane, std::vector<const GridObject*> visited) const {
    visited.push_back(this);

    int outputRow = getRow();
    int outputCol = getCol();
    getDirection().translate(outputRow, outputCol);

    if(!grid.isGridObjectAt(outputRow, outputCol)) {
        return false;
    }

    const GridObject* outputObject = grid.gridObjectAt(outputRow, outputCol);
    if(!outputObject->flowCanEnter(getDirection(), leftLane)) {
        return false;
    }

    bool flowEntersLeftLane = outputObject->flowEntersLeftLane(getDirection(), leftLane);
    bool flowHasPathToSink = outputObject->flowHasPathToSink(flowEntersLeftLane, visited);
    return flowHasPathToSink;
}

std::string Belt::selectedString() const {
    return "Belt - Output: " + getDirection().toString() + "\r\n" +
        "Path (L): " + (flowHasPathToSink(true, std::vector<const GridObject*>()) ? "T" : "F") +
        " (R): " + (flowHasPathToSink(false, std::vector<const GridObject*>()) ? "T" : "F");
}

void Belt::propagateFlow(FlowRecord* flowRecord, bool leftLane) const {
    if(!flowHasPathToSink(leftLane, std::vector<const GridObject*>())) {
        throw std::logic_error("Cannot propagate flow, no path to Sink!");
    }

    int nextRow = getRow();
    int nextCol = getCol();
    getDirection().translate(nextRow, nextCol);
    const GridObject* nextObject = grid.gridObjectAt(nextRow, nextCol);
    bool leftLaneNext = nextObject->flowEntersLeftLane(getDirection(), leftLane);

    nextObject->propagateFlow(new FlowRecord(flowRecord, flowRecord->amount, this, leftLane), leftLaneNext);
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

    if(grid.isGridObjectAt(behindRow, behindCol)) {
        if(grid.gridObjectAt(behindRow, behindCol)->getDirection() == getDirection()) {
            return getDirection();
        }
    }

    int cwRow = getRow();
    int cwCol = getCol();
    getDirection().clockwise().translate(cwRow, cwCol);
    bool cwIn = false;

    if(grid.isGridObjectAt(cwRow, cwCol)) {
        if(grid.gridObjectAt(cwRow, cwCol)->getDirection() == getDirection().counterClockwise()) {
            cwIn = true;
        }
    }

    int ccwRow = getRow();
    int ccwCol = getCol();
    getDirection().counterClockwise().translate(ccwRow, ccwCol);
    bool ccwIn = false;

    if(grid.isGridObjectAt(ccwRow, ccwCol)) {
        if(grid.gridObjectAt(ccwRow, ccwCol)->getDirection() == getDirection().clockwise()) {
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
