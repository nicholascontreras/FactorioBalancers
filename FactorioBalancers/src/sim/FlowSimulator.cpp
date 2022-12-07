#include "FlowSimulator.h"

#include <vector>

#include "../grid/gridObjects/Splitter.h"

#include "../grid/gridObjects/items/ItemSource.h"
#include "../grid/gridObjects/items/ItemSink.h"

void FlowSimulator::runSimulation(const Grid& grid) {
    for(GridObject* cur : grid.allGridObjects()) {
        cur->clearSimulationCounters();

        if(Splitter* curAsSplitter = dynamic_cast<Splitter*>(cur)) {
            curAsSplitter->resetOutputSides();
        }
    }

    for(int i = 0; i < 100; i++) {
        for(GridObject* cur : grid.allGridObjects()) {
            cur->advanceLanes();
        }

        for(GridObject* cur : grid.allGridObjects()) {
            cur->acceptIncomingItems();
        }
    }

    for(int i = 0; i < 100; i++) {
        for(GridObject* cur : grid.allGridObjects()) {
            if(dynamic_cast<ItemSource*>(cur)) {
                // Do nothing to cur if cur is an ItemSource
            } else {
                cur->advanceLanes();
            }
        }

        for(GridObject* cur : grid.allGridObjects()) {
            cur->acceptIncomingItems();
        }
    }
}
