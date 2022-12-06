#include "GridObject.h"

#include <stdexcept>

GridObject::GridObject(const Grid& grid, int row, int col, Direction direction) : grid(grid), row(row), col(col), direction(direction) {
    if(row < 0 || row >= grid.numRows || col < 0 || col >= grid.numCols) {
        throw std::invalid_argument("Position given is not on the Grid!");
    }
}

GridObject::~GridObject() {
}

void GridObject::draw(AsciiCanvas& canvas) const {
    canvas.draw(getCol() * 8, getRow() * 4, getImage());
}

GridObject::FlowRecord::FlowRecord(const FlowRecord* other) : 
    amount(other->amount),
    gridObject(other->gridObject),
    leftLane(other->leftLane) {

    if(other->prev != nullptr) {
        prev = new FlowRecord(other->prev);
    } else {
        prev = nullptr;
    }
}

GridObject::FlowRecord::FlowRecord(FlowRecord* prev, Fraction amount, const GridObject* gridObject, bool leftLane) :
    prev(prev), 
    amount(amount),
    gridObject(gridObject),
    leftLane(leftLane) {
}

GridObject::FlowRecord* GridObject::FlowRecord::recordContains(GridObject* gridObjectR, bool leftLaneR) {
    if(this->gridObject == gridObjectR && this->leftLane == leftLaneR) {
        return this;
    } else {
        return prev->recordContains(gridObjectR, leftLaneR);
    }
}

void GridObject::FlowRecord::deleteRecords() {
    if(prev != nullptr) {
        prev->deleteRecords();
    }
    delete this;
}
