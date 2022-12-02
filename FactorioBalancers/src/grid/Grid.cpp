#include "Grid.h"

// GridObject forward declared in header
#include "gridObjects/GridObject.h"

#include <algorithm>
#include <stdexcept>

Grid::Grid() {
}

Grid::~Grid() {
    std::for_each(gridItems.begin(), gridItems.end(), [](GridObject* cur) { delete cur; });
}

bool Grid::isGridObjectAt(int row, int col) const {
    return std::any_of(gridItems.begin(), gridItems.end(), [row, col](GridObject* cur) {
        return cur->getRow() == row && cur->getCol() == col;
    });
}

const GridObject* Grid::gridObjectAt(int row, int col) const {
    if(!isGridObjectAt(row, col)) {
        throw std::invalid_argument("No GridObject at given position!");
    }

    return *std::find_if(gridItems.begin(), gridItems.end(), [row, col](GridObject* cur) {
        return cur->getRow() == row && cur->getCol() == col;
    });
}

void Grid::addGridItem(GridObject* gridItem) {
    gridItems.push_back(gridItem);
}

const std::vector<GridObject*> Grid::allGridObjects() const {
    return gridItems;
}

AsciiCanvas Grid::draw() const {
    AsciiCanvas canvas(80, 20);

    std::for_each(gridItems.begin(), gridItems.end(), [&canvas](GridObject* cur) {
        cur->draw(canvas);
    });

    return canvas;
}
