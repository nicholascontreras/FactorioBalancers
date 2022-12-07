#pragma once

#include <vector>

#include "../grid/Grid.h"
#include "../grid/gridObjects/items/ItemSource.h"
#include "../grid/gridObjects/items/ItemSink.h"

class LayoutSolver {
public:
    void findLayout(Grid& grid);
private:
    void resetGrid(Grid& grid);
    bool addRandomToGrid(Grid& grid);
    bool testGrid(const Grid& grid);

    bool testWithSources(std::vector<ItemSource*> sources, std::vector<ItemSink*> sinks);
};