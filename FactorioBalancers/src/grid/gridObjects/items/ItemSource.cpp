#include "ItemSource.h"

#include <Windows.h>
#include <stdexcept>

ItemSource::ItemSource(const Grid& grid, int row, int col) :
    GridObject(grid, row, col, Direction::EAST) {
}

bool ItemSource::flowCanEnter(Direction incomingFlowDirection, bool leftLane) const {
    UNREFERENCED_PARAMETER(incomingFlowDirection);
    UNREFERENCED_PARAMETER(leftLane);
    return false;
}

bool ItemSource::flowEntersLeftLane(Direction incomingFlowDirection, bool leftLane) const {
    UNREFERENCED_PARAMETER(incomingFlowDirection);
    UNREFERENCED_PARAMETER(leftLane);
    throw std::logic_error("Flow cannot enter ItemSource!");
}

bool ItemSource::flowHasPathToSink(bool leftLane, std::vector<const GridObject*> visited) const {
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

std::string ItemSource::selectedString() const {
    return std::string("Item Source");
}

void ItemSource::propagateFlow(FlowRecord* flowRecord, bool leftLane) const {
    UNREFERENCED_PARAMETER(flowRecord);

    if(!flowHasPathToSink(leftLane, std::vector<const GridObject*>())) {
        throw std::logic_error("Cannot propagate flow, no path to Sink!");
    }

    int nextRow = getRow();
    int nextCol = getCol();
    getDirection().translate(nextRow, nextCol);
    const GridObject* nextObject = grid.gridObjectAt(nextRow, nextCol);
    bool leftLaneNext = nextObject->flowEntersLeftLane(getDirection(), leftLane);

    nextObject->propagateFlow(new FlowRecord(nullptr, 1, this, leftLane), leftLaneNext);
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
