#include "ItemSink.h"

#include <Windows.h>
#include <stdexcept>

ItemSink::ItemSink(const Grid& grid, int row, int col) :
    GridObject(grid, row, col, Direction::EAST),
    flowLeftLane(0),
    flowRightLane(0) {
}

bool ItemSink::flowCanEnter(Direction incomingFlowDirection, bool leftLane) const {
    UNREFERENCED_PARAMETER(incomingFlowDirection);
    UNREFERENCED_PARAMETER(leftLane);
    return incomingFlowDirection == getDirection();
}

bool ItemSink::flowEntersLeftLane(Direction incomingFlowDirection, bool leftLane) const {
    if(incomingFlowDirection != getDirection()) {
        throw std::invalid_argument("Input is not arriving from valid Direction!");
    }

    return leftLane;
}

bool ItemSink::flowHasPathToSink(bool leftLane, std::vector<const GridObject*> visited) const {
    UNREFERENCED_PARAMETER(leftLane);
    UNREFERENCED_PARAMETER(visited);
    return true;
}

std::string ItemSink::selectedString() const {
    return std::string("Item Sink\r\n") + 
        "Flow (L): " + flowLeftLane.toString() + " (R): " + flowRightLane.toString();
}

void ItemSink::propagateFlow(FlowRecord* flowRecord, bool leftLane) const {
    if(leftLane) {
        flowLeftLane = flowLeftLane + flowRecord->amount;
    } else {
        flowRightLane = flowRightLane + flowRecord->amount;
    }

    flowRecord->deleteRecords();
}

void ItemSink::resetFlowAmounts() {
    flowLeftLane = 0;
    flowRightLane = 0;
}

AsciiImage ItemSink::getImage() const {
    switch(getDirection()) {
    case Direction::EAST:
        return {
            "-------0",
            "      *|",
            "      *|",
            "-------2"
        };
    }

    throw std::invalid_argument("Invalid direction!");
}
