#include "ItemSource.h"

#include <stdexcept>

ItemSource::ItemSource(const Grid& grid, int row, int col) :
    GridObject(grid, row, col, Direction::EAST, new SimulationRecord()) {
}

bool ItemSource::flowCanEnter(Direction incomingFlowDirection, Lane lane) const {
    UNUSED(incomingFlowDirection);
    UNUSED(lane);
    return false;
}

GridObject::Lane ItemSource::flowEntersLane(Direction incomingFlowDirection, Lane lane) const {
    UNUSED(incomingFlowDirection);
    UNUSED(lane);
    throw std::logic_error("Flow cannot enter ItemSource!");
}

bool ItemSource::flowHasPathToSink(Lane lane, std::vector<const GridObject*> visited) const {
    visited.push_back(this);

    int outputRow = getRow();
    int outputCol = getCol();
    getDirection().translate(outputRow, outputCol);

    if(!grid.isGridObjectAt(outputRow, outputCol)) {
        return false;
    }

    const GridObject* outputObject = grid.gridObjectAt(outputRow, outputCol);
    if(!outputObject->flowCanEnter(getDirection(), lane)) {
        return false;
    }

    Lane flowEntersLane = outputObject->flowEntersLane(getDirection(), lane);
    bool flowHasPathToSink = outputObject->flowHasPathToSink(flowEntersLane, visited);
    return flowHasPathToSink;
}

void ItemSource::advanceLanes() {
    int nextRow = getRow();
    int nextCol = getCol();
    getDirection().translate(nextRow, nextCol);
    GridObject* nextObject = grid.gridObjectAt(nextRow, nextCol);

    if(nextObject->flowCanEnter(getDirection(), Lane::LEFT)) {
        Lane laneNext = nextObject->flowEntersLane(getDirection(), Lane::LEFT);
        if (nextObject->receiveItem(laneNext)) {
            simulationRecord->exportsLeftLane++;
        }
    }

    if(nextObject->flowCanEnter(getDirection(), Lane::RIGHT)) {
        Lane laneNext = nextObject->flowEntersLane(getDirection(), Lane::RIGHT);
        if (nextObject->receiveItem(laneNext)) {
            simulationRecord->exportsRightLane++;
        }
    }
}

std::string ItemSource::selectedString() const {
    return std::string("Item Source\r\n") +
    "Path (L): " + (flowHasPathToSink(Lane::LEFT, std::vector<const GridObject*>()) ? "T" : "F") +
        " (R): " + (flowHasPathToSink(Lane::RIGHT, std::vector<const GridObject*>()) ? "T" : "F") + "\r\n" +
    "Total (L): " + std::to_string(simulationRecord->exportsLeftLane) +
         " (R): " + std::to_string(simulationRecord->exportsRightLane);
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
