#pragma once

#include <vector>
#include <string>

#include "../grid/Grid.h"

class LayoutSolver {
public:
    static void findLayout(Grid& grid);
private:
    static void resetGrid(Grid& grid);
    static bool addRandomToGrid(Grid& grid);


};
