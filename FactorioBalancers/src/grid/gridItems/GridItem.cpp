#include "GridItem.h"

GridItem::GridItem(const Grid& grid, int row, int col, Direction direction) : grid(grid), row(row), col(col), direction(direction) {
}

GridItem::~GridItem() {
}

void GridItem::draw(AsciiCanvas& canvas) const {
    canvas.draw(getCol() * 8, getRow() * 4, getImage());
}
