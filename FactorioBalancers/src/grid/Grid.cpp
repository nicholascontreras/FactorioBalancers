#include "Grid.h"

// GridObject forward declared in header
#include "gridObjects/GridObject.h"

#include <algorithm>
#include <stdexcept>

Grid::Grid(int numRows, int numCols) : numRows(numRows), numCols(numCols) {
}

Grid::~Grid() {
    std::for_each(gridObjects.begin(), gridObjects.end(), [](GridObject* cur) { delete cur; });
}

bool Grid::isGridObjectAt(int row, int col) const {
    return std::any_of(gridObjects.begin(), gridObjects.end(), [row, col](GridObject* cur) {
        return cur->getRow() == row && cur->getCol() == col;
    });
}

GridObject* Grid::gridObjectAt(int row, int col) const {
    if(!isGridObjectAt(row, col)) {
        throw std::invalid_argument("No GridObject at given position!");
    }

    return *std::find_if(gridObjects.begin(), gridObjects.end(), [row, col](GridObject* cur) {
        return cur->getRow() == row && cur->getCol() == col;
    });
}

void Grid::addGridObject(GridObject* gridItem) {
    gridObjects.push_back(gridItem);
}

void Grid::removeGridObject(int row, int col) {
    if(!isGridObjectAt(row, col)) {
        throw std::invalid_argument("No GridObject at given position!");
    }

    gridObjects.erase(std::remove(gridObjects.begin(), gridObjects.end(), gridObjectAt(row, col)), gridObjects.end());
}

const std::vector<GridObject*> Grid::allGridObjects() const {
    return gridObjects;
}

AsciiCanvas Grid::draw() const {
    AsciiCanvas canvas(numCols * 8, numRows * 4);

    std::for_each(gridObjects.begin(), gridObjects.end(), [&canvas](GridObject* cur) {
        cur->draw(canvas);
    });

    return canvas;
}
