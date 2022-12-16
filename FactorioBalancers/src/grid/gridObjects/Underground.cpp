#include "Underground.h"

#include <stdexcept>

Underground::Underground(const Grid& grid, int row, int col, Direction direction, bool down) :
    GridObject(grid, row, col, direction, new SimulationRecord()),
    down(down) {
}

bool Underground::flowCanEnter(Direction incomingFlowDirection, Lane lane) const {
    if(down) {
        if(incomingFlowDirection == getDirection()) {
            return true;
        } else if(incomingFlowDirection == getDirection().clockwise()) {
            return lane == Lane::RIGHT;
        } else if(incomingFlowDirection == getDirection().counterClockwise()) {
            return lane == Lane::LEFT;
        } else if(incomingFlowDirection == getDirection().reverse()) {
            return false;
        }
    } else {
        if(incomingFlowDirection == getDirection()) {
            return false;
        } else if(incomingFlowDirection == getDirection().clockwise()) {
            return lane == Lane::LEFT;
        } else if(incomingFlowDirection == getDirection().counterClockwise()) {
            return lane == Lane::RIGHT;
        } else if(incomingFlowDirection == getDirection().reverse()) {
            return false;
        }
    }
    throw std::invalid_argument("Invalid flow Direction!");
}

GridObject::Lane Underground::flowEntersLane(Direction incomingFlowDirection, Lane lane) const {
    if(down) {
        if(incomingFlowDirection == getDirection()) {
            return lane;
        } else if(incomingFlowDirection == getDirection().clockwise()) {
            return Lane::LEFT;
        } else if(incomingFlowDirection == getDirection().counterClockwise()) {
            return Lane::RIGHT;
        }
    } else {
        if(incomingFlowDirection == getDirection().clockwise()) {
            return Lane::LEFT;
        } else if(incomingFlowDirection == getDirection().counterClockwise()) {
            return Lane::RIGHT;
        }
    }
    throw std::invalid_argument("Input is not arriving from valid Direction!");
}

bool Underground::flowHasPathToSink(Lane lane, std::vector<std::pair<const GridObject*, Lane>> visited) const {
    visited.push_back({ this, lane });
    
    if(down) {
        Underground* myUp = getOtherHalf();
        if(myUp != nullptr) {
            return myUp->flowHasPathToSink(lane, visited);
        } else {
            return false;
        }
    } else {
        int outputRow = getRow();
        int outputCol = getCol();
        getDirection().translate(outputRow, outputCol);

        if(!grid.isOnGrid(outputRow, outputCol)) {
            return false;
        }

        if(!grid.isGridObjectAt(outputRow, outputCol)) {
            return false;
        }

        GridObject* outputObject = grid.gridObjectAt(outputRow, outputCol);
        if(!outputObject->flowCanEnter(getDirection(), lane)) {
            return false;
        }

        Lane flowEntersLane = outputObject->flowEntersLane(getDirection(), lane);
        bool flowHasPathToSink = outputObject->flowHasPathToSink(flowEntersLane, visited);
        return flowHasPathToSink;
    }
}

void Underground::advanceLanes() {
    if(down) {
        Underground* otherHalf = getOtherHalf();
        if(otherHalf != nullptr) {
            if(laneHasItem(Lane::LEFT)) {
                if(otherHalf->receiveItem(Lane::LEFT)) {
                    simulationRecord->exportsLeftLane++;
                    simulationRecord->itemsLeftLane--;
                }
            }

            if(laneHasItem(Lane::RIGHT)) {
                if(otherHalf->receiveItem(Lane::RIGHT)) {
                    simulationRecord->exportsRightLane++;
                    simulationRecord->itemsRightLane--;
                }
            }
        }
    } else {
        int nextRow = getRow();
        int nextCol = getCol();
        getDirection().translate(nextRow, nextCol);

        if(grid.isOnGrid(nextRow, nextCol)) {
            if(grid.isGridObjectAt(nextRow, nextCol)) {
                GridObject* nextObject = grid.gridObjectAt(nextRow, nextCol);

                if(laneHasItem(Lane::LEFT)) {
                    if(nextObject->flowCanEnter(getDirection(), Lane::LEFT)) {

                        Lane laneNext = nextObject->flowEntersLane(getDirection(), Lane::LEFT);
                        if(nextObject->receiveItem(laneNext)) {
                            simulationRecord->exportsLeftLane++;
                            simulationRecord->itemsLeftLane--;
                        }
                    }
                }

                if(laneHasItem(Lane::RIGHT)) {
                    if(nextObject->flowCanEnter(getDirection(), Lane::RIGHT)) {

                        Lane laneNext = nextObject->flowEntersLane(getDirection(), Lane::RIGHT);
                        if(nextObject->receiveItem(laneNext)) {
                            simulationRecord->exportsRightLane++;
                            simulationRecord->itemsRightLane--;
                        }
                    }
                }
            }
        }
    }
}

bool Underground::isDown() const {
    return down;
}

std::string Underground::selectedString() const {
    return std::string("Underground Belt (") + (down ? "Entry" : "Exit") + ") - Ouput: " + getDirection().toString() + "\r\n" +
        "Items (L): " + std::to_string(simulationRecord->itemsLeftLane) +
             " (R): " + std::to_string(simulationRecord->itemsRightLane);
}

AsciiImage Underground::getImage() const {
    if(down) {
        switch(getDirection()) {
        case Direction::NORTH:
            return {
                "        ",
                "3------0",
                "| ^  ^ |",
                "|      |"
            };
        case Direction::EAST:
            return {
                "-----0  ",
                "   > |  ",
                "   > |  ",
                "-----2  "
            };
        case Direction::SOUTH:
            return {
                "|      |",
                "| V  V |",
                "1------2",
                "        "
            };
        case Direction::WEST:
            return {
                "  3------",
                "  | <    ",
                "  | <    ",
                "  1------"
            };
        }
    } else {
        switch(getDirection()) {
        case Direction::NORTH:
            return {
                "|      |",
                "| ^  ^ |",
                "1------2",
                "        "
            };
        case Direction::EAST:
            return {
                "  3------",
                "  | >    ",
                "  | >    ",
                "  1------"
            };
            
        case Direction::SOUTH:
            return {
                "        ",
                "3------0",
                "| V  V |",
                "|      |"
            };
        case Direction::WEST:
            return {
                "-----0  ",
                "   < |  ",
                "   < |  ",
                "-----2  "
            };
        }
    }

    throw std::invalid_argument("Invalid direction!");
}

Underground* Underground::getOtherHalf() const {
    int otherHalfRow = getRow();
    int otherHalfCol = getCol();

    Direction otherHalfDir = down ? getDirection() : getDirection().reverse();
    for(int i = 0; i < 9; i++) {
        otherHalfDir.translate(otherHalfRow, otherHalfCol);

        if(grid.isOnGrid(otherHalfRow, otherHalfCol)) {
            if(grid.isGridObjectAt(otherHalfRow, otherHalfCol)) {
                GridObject* go = grid.gridObjectAt(otherHalfRow, otherHalfCol);
                Underground* casted = dynamic_cast<Underground*>(go);
                if(casted != nullptr) {
                    if(casted->getDirection() == getDirection()) {
                        if(casted->down == down) {
                            return nullptr;
                        } else {
                            return casted;
                        }
                    }
                }
            }
        }
    }
    return nullptr;
}
