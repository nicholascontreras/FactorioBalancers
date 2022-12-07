#include "GridObject.h"

#include <stdexcept>

int GridObject::MAX_ITEMS_PER_LANE = 4;

GridObject::GridObject(const Grid& grid, int row, int col, Direction direction, SimulationRecord* simulationRecord) :
    grid(grid),
    row(row),
    col(col),
    direction(direction),
    simulationRecord(simulationRecord) {

    if(row < 0 || row >= grid.numRows || col < 0 || col >= grid.numCols) {
        throw std::invalid_argument("Position given is not on the Grid!");
    }
}

GridObject::~GridObject() {
    delete simulationRecord;
}

void GridObject::draw(AsciiCanvas& canvas) const {
    canvas.draw(getCol() * 8, getRow() * 4, getImage());
}

void GridObject::acceptIncomingItems() {
    simulationRecord->itemsLeftLane += simulationRecord->incomingItemsLeftLane;
    simulationRecord->itemsRightLane += simulationRecord->incomingItemsRightLane;

    simulationRecord->incomingItemsLeftLane = 0;
    simulationRecord->incomingItemsRightLane = 0;
}

bool GridObject::receiveItem(Lane lane) {
    if(isLaneFull(lane)) {
        if(lane == Lane::LEFT) {
            simulationRecord->blockedInsertionsLeftLane++;
        } else if(lane == Lane::RIGHT) {
            simulationRecord->blockedInsertionsRightLane++;
        } else {
            throw std::invalid_argument("Invalid Lane!");
        }
        return false;
    } else {
        if(lane == Lane::LEFT) {
            simulationRecord->incomingItemsLeftLane++;
        } else if(lane == Lane::RIGHT) {
            simulationRecord->incomingItemsRightLane++;
        } else {
            throw std::invalid_argument("Invalid Lane!");
        }
        return true;
    }
}

bool GridObject::laneHasItem(Lane lane) {
    return (lane == Lane::LEFT ? simulationRecord->itemsLeftLane : simulationRecord->itemsRightLane) > 0;
}

bool GridObject::isLaneFull(Lane lane) {
    return (lane == Lane::LEFT ? simulationRecord->itemsLeftLane + simulationRecord->incomingItemsLeftLane : simulationRecord->itemsRightLane + simulationRecord->incomingItemsRightLane) >= MAX_ITEMS_PER_LANE;
}

void GridObject::clearSimulationCounters() {
    simulationRecord->itemsLeftLane = 0;
    simulationRecord->itemsRightLane = 0;
    simulationRecord->incomingItemsLeftLane = 0;
    simulationRecord->incomingItemsRightLane = 0;

    simulationRecord->successfulInsertionsLeftLane = 0;
    simulationRecord->successfulInsertionsRightLane = 0;
    simulationRecord->blockedInsertionsLeftLane = 0;
    simulationRecord->blockedInsertionsRightLane = 0;
    simulationRecord->exportsLeftLane = 0;
    simulationRecord->exportsRightLane = 0;
}

const GridObject::SimulationRecord* GridObject::getSimulationRecord() const {
    return simulationRecord;
}
