#pragma once

#include "../grid/Grid.h"
#include "../grid/gridObjects/items/ItemSource.h"
#include "../grid/gridObjects/items/ItemSink.h"

class FlowSimulator {
public:
    static void runSimulation(const Grid& grid, int numTestItems, std::vector<ItemSource*> enabledSources, std::vector<ItemSink*> enabledSinks);
    static void stepSimulation(const Grid& grid);
    static void resetSimulation(const Grid& grid);
};
