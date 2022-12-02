#include "GridObject.h"

GridObject::GridObject(const Grid& grid, int row, int col, Direction direction) : grid(grid), row(row), col(col), direction(direction) {
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

void GridObject::FlowRecord::deleteRecords(FlowRecord* deleteTo) {
    if(prev != deleteTo) {
        prev->deleteRecords(deleteTo);
    }
    delete this;
}
