#include "LayoutSolver.h"

#include <random>
#include <stdexcept>

#include "../grid/gridObjects/Belt.h"
#include "../grid/gridObjects/Splitter.h"
#include "../grid/gridObjects/Underground.h"
#include "../grid/gridObjects/items/ItemSource.h"
#include "../grid/gridObjects/items/ItemSink.h"

void LayoutSolver::findLayout(Grid& grid) {
    resetGrid(grid);
}

void LayoutSolver::resetGrid(Grid& grid) {
    std::vector<const GridObject*> toRemove;
    for(const GridObject* go : grid.allGridObjects()) {
        const ItemSource* source = dynamic_cast<const ItemSource*>(go);
        const ItemSink* sink = dynamic_cast<const ItemSink*>(go);
        if(source == nullptr && sink == nullptr) {
            toRemove.push_back(go);
        }
    }

    for(const GridObject* go : toRemove) {
        grid.removeGridObject(go->getRow(), go->getCol());
    }
}

bool LayoutSolver::addRandomToGrid(Grid& grid) {
    std::mt19937 rg(std::random_device());

    for (int i = 0; i < 1000; i++) {
        int row = std::uniform_int_distribution(0, grid.numRows)(rg);
        int col = std::uniform_int_distribution(0, grid.numCols)(rg);

        if(grid.isGridObjectAt(row, col)) {
            continue;
        }

        int objectType = std::uniform_int_distribution(0, 2)(rg);
        Direction direction = std::uniform_int_distribution(0, 3)(rg);

        switch(objectType) {
        case 0: // Belt
            grid.addGridObject(new Belt(grid, row, col, direction));
            return true;
        case 1: // Splitter
            int otherRow = row;
            int otherCol = col;
            direction.clockwise().translate(otherRow, otherCol);
            if(grid.isGridObjectAt(otherRow, otherCol)) {
                continue;
            }
            grid.addGridObject(new Splitter(grid, row, col, direction, true));
            grid.addGridObject(new Splitter(grid, otherRow, otherCol, direction, false));
            return true;
        case 2: // Underground
            bool down = std::uniform_int_distribution(0, 1)(rg) == 1;
            grid.addGridObject(new Underground(grid, row, col, direction, down));
            return true;
        default:
            throw std::logic_error("Invalid object type index!");
        }
    }

    return false;
}

bool LayoutSolver::testGrid(const Grid& grid) {
    return false;
}