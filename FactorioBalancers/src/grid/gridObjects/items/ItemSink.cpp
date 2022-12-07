#include "ItemSink.h"

#include <Windows.h>
#include <stdexcept>

ItemSink::ItemSink(const Grid& grid, int row, int col) :
    GridObject(grid, row, col, Direction::EAST, new SimulationRecord()) {
}

bool ItemSink::flowCanEnter(Direction incomingFlowDirection, Lane lane) const {
    UNREFERENCED_PARAMETER(incomingFlowDirection);
    UNREFERENCED_PARAMETER(lane);
    return incomingFlowDirection == getDirection();
}

GridObject::Lane ItemSink::flowEntersLane(Direction incomingFlowDirection, Lane lane) const {
    if(incomingFlowDirection != getDirection()) {
        throw std::invalid_argument("Input is not arriving from valid Direction!");
    }

    return lane;
}

bool ItemSink::flowHasPathToSink(Lane lane, std::vector<const GridObject*> visited) const {
    UNREFERENCED_PARAMETER(lane);
    UNREFERENCED_PARAMETER(visited);
    return true;
}

void ItemSink::advanceLanes() {
    if(laneHasItem(Lane::LEFT)) {
        simulationRecord->itemsLeftLane--;
        simulationRecord->exportsLeftLane++;

        std::cout << "ItemSink pushed item left" << std::endl;
    }
    if(laneHasItem(Lane::RIGHT)) {
        simulationRecord->itemsRightLane--;
        simulationRecord->exportsRightLane++;

        std::cout << "ItemSink pushed item right" << std::endl;
    }
}

std::string ItemSink::selectedString() const {
    return std::string("Item Sink\r\n") + 
        "Total (L): " + std::to_string(simulationRecord->exportsLeftLane) + 
             " (R): " + std::to_string(simulationRecord->exportsRightLane);
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
