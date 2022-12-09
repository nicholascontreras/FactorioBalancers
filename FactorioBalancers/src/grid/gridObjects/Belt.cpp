#include "Belt.h"

#include <Windows.h>
#include <stdexcept>

#include "Underground.h"

Belt::Belt(const Grid& grid, int row, int col, Direction direction) : 
    GridObject(grid, row, col, direction, new SimulationRecord()) {
}

bool Belt::flowCanEnter(Direction incomingFlowDirection, Lane lane) const {
    UNREFERENCED_PARAMETER(lane);
    return incomingFlowDirection != getDirection().reverse();
}

GridObject::Lane Belt::flowEntersLane(Direction incomingFlowDirection, Lane lane) const {
    Direction beltInputDirection = determineInputDirection();
    
    if(incomingFlowDirection == beltInputDirection) {
        return lane;
    } else if(incomingFlowDirection == beltInputDirection.clockwise()) {
        return Lane::LEFT;
    } else if(incomingFlowDirection == beltInputDirection.counterClockwise()) {
        return Lane::RIGHT;
    } else {
        throw std::invalid_argument("Input is not arriving from valid Direction!");
    }
}

bool Belt::flowHasPathToSink(Lane lane, std::vector<const GridObject*> visited) const {
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

void Belt::advanceLanes() {
    int nextRow = getRow();
    int nextCol = getCol();
    getDirection().translate(nextRow, nextCol);

    if(!grid.isGridObjectAt(nextRow, nextCol)) {
        return;
    }
    GridObject* nextObject = grid.gridObjectAt(nextRow, nextCol);

    if(laneHasItem(Lane::LEFT)) {
        if(nextObject->flowCanEnter(getDirection(), Lane::LEFT)) {

            Lane laneNext = nextObject->flowEntersLane(getDirection(), Lane::LEFT);
            if (nextObject->receiveItem(laneNext)) {
                simulationRecord->exportsLeftLane++;
                simulationRecord->itemsLeftLane--;
            }
        }
    }

    if(laneHasItem(Lane::RIGHT)) {
        if(nextObject->flowCanEnter(getDirection(), Lane::RIGHT)) {

            Lane laneNext = nextObject->flowEntersLane(getDirection(), Lane::RIGHT);
            if (nextObject->receiveItem(laneNext)) {
                simulationRecord->exportsRightLane++;
                simulationRecord->itemsRightLane--;
            }
        }
    }
}

std::string Belt::selectedString() const {
    return "Belt - Output: " + getDirection().toString() + "\r\n" +
        "Path (L): " + (flowHasPathToSink(Lane::LEFT, std::vector<const GridObject*>()) ? "T" : "F") +
        " (R): " + (flowHasPathToSink(Lane::RIGHT, std::vector<const GridObject*>()) ? "T" : "F") + "\r\n" + 
        "Items (L): " + std::to_string(simulationRecord->itemsLeftLane) + 
             " (R): " + std::to_string(simulationRecord->itemsRightLane);
}

AsciiImage Belt::getImage() const {
    Direction inputDirection = determineInputDirection();
    
    if(inputDirection == Direction::SOUTH) {
        switch(getDirection()) {
        case Direction::WEST:
            return {
                "2      |",
                "<      |",
                "<      |",
                "-------2"
            };
        case Direction::SOUTH:
            return {
                "|      |",
                "|      |",
                "|      |",
                "| V  V |"
            };
        case Direction::EAST:
            return {
                "|      1",
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
        GridObject* behind = grid.gridObjectAt(behindRow, behindCol);
        if(behind->getDirection() == getDirection()) {
            if(Underground* asUnderground = dynamic_cast<Underground*>(behind)) {
                if(!asUnderground->isDown()) {
                    return getDirection();
                }
            } else {
                return getDirection();
            }
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
