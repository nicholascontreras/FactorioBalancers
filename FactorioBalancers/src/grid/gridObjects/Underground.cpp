#include "Underground.h"

#include <stdexcept>

Underground::Underground(const Grid& grid, int row, int col, Direction direction, bool down) :
    GridObject(grid, row, col, direction),
    down(down) {
}

bool Underground::flowCanEnter(Direction incomingFlowDirection, bool leftLane) const {
    if(down) {
        if(incomingFlowDirection == getDirection()) {
            return true;
        } else if(incomingFlowDirection == getDirection().clockwise()) {
            return !leftLane;
        } else if(incomingFlowDirection == getDirection().counterClockwise()) {
            return leftLane;
        } else if(incomingFlowDirection == getDirection().reverse()) {
            return false;
        }
    } else {
        if(incomingFlowDirection == getDirection()) {
            return false;
        } else if(incomingFlowDirection == getDirection().clockwise()) {
            return leftLane;
        } else if(incomingFlowDirection == getDirection().counterClockwise()) {
            return !leftLane;
        } else if(incomingFlowDirection == getDirection().reverse()) {
            return false;
        }
    }
    throw std::invalid_argument("Invalid flow Direction!");
}

bool Underground::flowEntersLeftLane(Direction incomingFlowDirection, bool leftLane) const {
    if(down) {
        if(incomingFlowDirection == getDirection()) {
            return leftLane;
        } else if(incomingFlowDirection == getDirection().clockwise()) {
            return true;
        } else if(incomingFlowDirection == getDirection().counterClockwise()) {
            return false;
        }
    } else {
        if(incomingFlowDirection == getDirection().clockwise()) {
            return true;
        } else if(incomingFlowDirection == getDirection().counterClockwise()) {
            return false;
        }
    }
    throw std::invalid_argument("Input is not arriving from valid Direction!");
}

bool Underground::flowHasPathToSink(bool leftLane, std::vector<const GridObject*> visited) const {
    visited.push_back(this);
    
    if(down) {
        int upRow = getRow();
        int upCol = getCol();
        for(int i = 0; i < 9; i++) {
            getDirection().translate(upRow, upCol);

            if(grid.isGridObjectAt(upRow, upCol)) {
                const GridObject* go = grid.gridObjectAt(upRow, upCol);
                const Underground* casted = dynamic_cast<const Underground*>(go);
                if(casted != nullptr) {
                    if(casted->down) {
                        return false;
                    } else {
                        return casted->flowHasPathToSink(leftLane, visited);
                    }
                }
            }
        }
        return false;
    } else {
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
}

std::string Underground::selectedString() const {
    return std::string("Underground Belt (") + (down ? "Entry" : "Exit") + ") - Ouput: " + getDirection().toString();
}

void Underground::propagateFlow(FlowRecord* flowRecord, bool leftLane) const {
}

AsciiImage Underground::getImage() const {
    if(down) {
        switch(getDirection()) {
        case Direction::NORTH:
            return {
                "       ",
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
                "       ",
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
