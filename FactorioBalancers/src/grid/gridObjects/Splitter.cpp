#include "Splitter.h"

#include <Windows.h>
#include <stdexcept>

Splitter::Splitter(const Grid& grid, int row, int col, Direction direction, bool leftHalf) : 
    GridObject(grid, row, col, direction),
    leftHalf(leftHalf) {
}

bool Splitter::flowCanEnter(Direction incomingFlowDirection, bool leftLane) const {
    UNREFERENCED_PARAMETER(leftLane);
    return incomingFlowDirection == getDirection();
}

bool Splitter::flowEntersLeftLane(Direction incomingFlowDirection, bool leftLane) const {
    if(incomingFlowDirection != getDirection()) {
        throw std::invalid_argument("Input is not arriving from valid Direction!");
    }

    return leftLane;
}

bool Splitter::flowHasPathToSink(bool leftLane, std::vector<const GridObject*> visited) const {
    visited.push_back(this);

    if(std::find(visited.begin(), visited.end(), dynamic_cast<const GridObject*>(getOtherHalf())) == visited.end()) {
        bool otherSide = getOtherHalf()->flowHasPathToSink(leftLane, visited);
        if(otherSide) {
            return true;
        }
    }

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

std::string Splitter::selectedString() const {
    return std::string("Splitter (") + (leftHalf ? "Left" : "Right") + " Half) - Output: " + getDirection().toString();
}

void Splitter::propagateFlow(FlowRecord* flowRecord, bool leftLane) const {
    if(!flowHasPathToSink(leftLane, std::vector<const GridObject*>())) {
        throw std::logic_error("Cannot propagate flow, no path to Sink!");
    }

    int nextRow = getRow();
    int nextCol = getCol();
    getDirection().translate(nextRow, nextCol);
    const GridObject* nextObject = grid.gridObjectAt(nextRow, nextCol);
    bool leftLaneNext = nextObject->flowEntersLeftLane(getDirection(), leftLane);
    bool flowPastMe = nextObject->flowHasPathToSink(leftLaneNext, std::vector<const GridObject*>());

    const Splitter* otherHalf = getOtherHalf();
    int nextRowOther = otherHalf->getRow();
    int nextColOther = otherHalf->getCol();
    getDirection().translate(nextRowOther, nextColOther);
    const GridObject* nextObjectOther = grid.gridObjectAt(nextRowOther, nextColOther);
    bool leftLaneNextOther = nextObjectOther->flowEntersLeftLane(getDirection(), leftLane);
    bool flowPastOther = nextObjectOther->flowHasPathToSink(leftLaneNextOther, std::vector<const GridObject*>());

    if(flowPastMe && flowPastOther) {
        Fraction amountEachSide = flowRecord->amount / 2;
        nextObject->propagateFlow(new FlowRecord(new FlowRecord(flowRecord), amountEachSide, this, leftLane), leftLaneNext);
        nextObjectOther->propagateFlow(new FlowRecord(flowRecord, amountEachSide, this, leftLane), leftLaneNextOther);
    } else if(flowPastMe) {
        nextObject->propagateFlow(new FlowRecord(flowRecord, flowRecord->amount, this, leftLane), leftLaneNext);
    } else if(flowPastOther) {
        nextObjectOther->propagateFlow(new FlowRecord(flowRecord, flowRecord->amount, this, leftLane), leftLaneNextOther);
    } else {
        throw std::logic_error("No flow on either Spliter output!");
    }
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

const Splitter* Splitter::getOtherHalf() const {
    if(leftHalf) {
        int rightRow = getRow();
        int rightCol = getCol();
        getDirection().clockwise().translate(rightRow, rightCol);
        return dynamic_cast<const Splitter*>(grid.gridObjectAt(rightRow, rightCol));
    } else {
        int leftRow = getRow();
        int leftCol = getCol();
        getDirection().counterClockwise().translate(leftRow, leftCol);
        return dynamic_cast<const Splitter*>(grid.gridObjectAt(leftRow, leftCol));
    }
}
