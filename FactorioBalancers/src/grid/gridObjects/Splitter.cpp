#include "Splitter.h"

#include <stdexcept>

#include <random>

Splitter::Splitter(const Grid& grid, int row, int col, Direction direction, SplitterSide side) :
    GridObject(grid, row, col, direction, new SplitterSimulationRecord()),
    side(side) {
}

bool Splitter::flowCanEnter(Direction incomingFlowDirection, Lane lane) const {
    UNUSED(lane);
    return incomingFlowDirection == getDirection();
}

GridObject::Lane Splitter::flowEntersLane(Direction incomingFlowDirection, Lane lane) const {
    if(incomingFlowDirection != getDirection()) {
        throw std::invalid_argument("Input is not arriving from valid Direction!");
    }

    return lane;
}

bool Splitter::flowHasPathToSink(Lane lane, std::vector<std::pair<const GridObject*, Lane>> visited) const {
    visited.push_back({ this, lane });

    if(std::find(visited.begin(), visited.end(), std::pair<const GridObject*, Lane>(getOtherHalf(), lane)) == visited.end()) {
        bool otherSide = getOtherHalf()->flowHasPathToSink(lane, visited);
        if(otherSide) {
            return true;
        }
    }

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

    if(std::find(visited.begin(), visited.end(), std::pair<const GridObject*, Lane>(outputObject, lane)) != visited.end()) {
        return false;
    }

    bool flowHasPathToSink = outputObject->flowHasPathToSink(flowEntersLane, visited);
    return flowHasPathToSink;
}

void Splitter::advanceLanes() {
    int afterRow = getRow();
    int afterCol = getCol();
    getDirection().translate(afterRow, afterCol);
    GridObject* afterMe = nullptr;
    if(grid.isOnGrid(afterRow, afterCol)) {
        if(grid.isGridObjectAt(afterRow, afterCol)) {
            afterMe = grid.gridObjectAt(afterRow, afterCol);
        }
    }

    if(side == SplitterSide::LEFT) {
        getDirection().clockwise().translate(afterRow, afterCol);
    } else if(side == SplitterSide::RIGHT) {
        getDirection().counterClockwise().translate(afterRow, afterCol);
    } else {
        throw std::logic_error("Invalid SplitterSide!");
    }

    GridObject* afterOther = nullptr;
    if(grid.isOnGrid(afterRow, afterCol)) {
        if(grid.isGridObjectAt(afterRow, afterCol)) {
            afterOther = grid.gridObjectAt(afterRow, afterCol);
        }
    }

    if(laneHasItem(Lane::LEFT)) {
        GridObject* preferred = afterMe;
        GridObject* backup = afterOther;
        if(getSplitterSimRecord()->leftLaneOutput != side) {
            preferred = afterOther;
            backup = afterMe;
        }

        bool outputFound = false;

        if(preferred != nullptr && preferred->flowCanEnter(getDirection(), Lane::LEFT)) {
            Lane laneNextPreferred = preferred->flowEntersLane(getDirection(), Lane::LEFT);
            if(preferred->receiveItem(laneNextPreferred)) {
                outputFound = true;

                simulationRecord->exportsLeftLane++;
                simulationRecord->itemsLeftLane--;
                getSplitterSimRecord()->toggleOutput(Lane::LEFT);
                getOtherHalf()->getSplitterSimRecord()->toggleOutput(Lane::LEFT);
            }
        }

        if(!outputFound) {
            if(backup != nullptr && backup->flowCanEnter(getDirection(), Lane::LEFT)) {

                Lane laneNextBackup = backup->flowEntersLane(getDirection(), Lane::LEFT);
                if(backup->receiveItem(laneNextBackup)) {
                    simulationRecord->exportsLeftLane++;
                    simulationRecord->itemsLeftLane--;
                }
            }
        }
    }

    if(laneHasItem(Lane::RIGHT)) {
        GridObject* preferred = afterMe;
        GridObject* backup = afterOther;
        if(getSplitterSimRecord()->rightLaneOutput != side) {
            preferred = afterOther;
            backup = afterMe;
        }

        bool outputFound = false;

        if(preferred != nullptr && preferred->flowCanEnter(getDirection(), Lane::RIGHT)) {
            Lane laneNextPreferred = preferred->flowEntersLane(getDirection(), Lane::RIGHT);
            if(preferred->receiveItem(laneNextPreferred)) {
                outputFound = true;

                simulationRecord->exportsRightLane++;
                simulationRecord->itemsRightLane--;
                getSplitterSimRecord()->toggleOutput(Lane::RIGHT);
                getOtherHalf()->getSplitterSimRecord()->toggleOutput(Lane::RIGHT);
            }
        }

        if(!outputFound) {
            if(backup != nullptr && backup->flowCanEnter(getDirection(), Lane::RIGHT)) {

                Lane laneNextBackup = backup->flowEntersLane(getDirection(), Lane::RIGHT);
                if(backup->receiveItem(laneNextBackup)) {
                    simulationRecord->exportsRightLane++;
                    simulationRecord->itemsRightLane--;
                }
            }
        }
    }
}

void Splitter::resetOutputSides() {
    getSplitterSimRecord()->leftLaneOutput = SplitterSide::LEFT;
    getSplitterSimRecord()->rightLaneOutput = SplitterSide::LEFT;
}

std::string Splitter::selectedString() const {
    return std::string("Splitter (") + (side == SplitterSide::LEFT ? "Left" : "Right") + " Half) - Output: " + getDirection().toString() + "\r\n" +
        "Items (L): " + std::to_string(simulationRecord->itemsLeftLane) +
             " (R): " + std::to_string(simulationRecord->itemsRightLane);
}

AsciiImage Splitter::getImage() const {
    if(side == SplitterSide::LEFT) {
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
    } else if (side == SplitterSide::RIGHT) {
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

    throw std::logic_error("Invalid SplitterSide or Direction!");
}

Splitter* Splitter::getOtherHalf() const {
    if(side == SplitterSide::LEFT) {
        int rightRow = getRow();
        int rightCol = getCol();
        getDirection().clockwise().translate(rightRow, rightCol);
        return (Splitter*)grid.gridObjectAt(rightRow, rightCol);
    } else if (side == SplitterSide::RIGHT) {
        int leftRow = getRow();
        int leftCol = getCol();
        getDirection().counterClockwise().translate(leftRow, leftCol);
        return (Splitter*)grid.gridObjectAt(leftRow, leftCol);
    } else {
        throw std::logic_error("Invalid SplitterSide!");
    }
}

Splitter::SplitterSimulationRecord* Splitter::getSplitterSimRecord() const {
    return (SplitterSimulationRecord*)simulationRecord;
}

void Splitter::SplitterSimulationRecord::toggleOutput(Lane lane) {
    if(lane == Lane::LEFT) {
        leftLaneOutput = leftLaneOutput == SplitterSide::LEFT ? SplitterSide::RIGHT : SplitterSide::LEFT;
    } else if(lane == Lane::RIGHT) {
        rightLaneOutput = rightLaneOutput == SplitterSide::LEFT ? SplitterSide::RIGHT : SplitterSide::LEFT;
    } else {
        throw std::invalid_argument("Invalid Lane!");
    }
}
