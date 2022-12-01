#include "Grid.h"

// GridItem forward declared in header
#include "gridItems/GridItem.h"

#include <algorithm>
#include <stdexcept>

Grid::Grid() {
}

Grid::~Grid() {
    std::for_each(gridItems.begin(), gridItems.end(), [](GridItem* cur) { delete cur; });
}

bool Grid::isGridItemAt(int row, int col) const {
    return std::any_of(gridItems.begin(), gridItems.end(), [row, col](GridItem* cur) {
        return cur->getRow() == row && cur->getCol() == col;
    });
}

const GridItem* Grid::gridItemAt(int row, int col) const {
    if(!isGridItemAt(row, col)) {
        throw std::invalid_argument("No GridItem at given position!");
    }

    return *std::find_if(gridItems.begin(), gridItems.end(), [row, col](GridItem* cur) {
        return cur->getRow() == row && cur->getCol() == col;
    });
}

void Grid::addGridItem(GridItem* gridItem) {
    gridItems.push_back(gridItem);
}

AsciiCanvas Grid::draw() const {
    AsciiCanvas canvas(80, 20);

    std::for_each(gridItems.begin(), gridItems.end(), [&canvas](GridItem* cur) {
        cur->draw(canvas);
    });

    return canvas;
}
