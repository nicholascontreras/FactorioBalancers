#pragma once
#include "../grid/Grid.h"

class LayoutSolver {
public:
    void findLayout(Grid& grid);
private:
    void resetGrid(Grid& grid);
    bool addRandomToGrid(Grid& grid);
    bool testGrid(const Grid& grid);
};