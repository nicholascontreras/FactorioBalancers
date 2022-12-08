#pragma once

#include <vector>
#include <string>

#include "../grid/Grid.h"

class LayoutSolver {
public:
    void findLayout(Grid& grid);
private:
    void resetGrid(Grid& grid);
    bool addRandomToGrid(Grid& grid);


};
