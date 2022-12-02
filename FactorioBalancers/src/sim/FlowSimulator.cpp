#include "FlowSimulator.h"

#include <vector>

#include "../grid/gridObjects/items/ItemSource.h"
#include "../grid/gridObjects/items/ItemSink.h"

void FlowSimulator::runSimulation(const Grid& grid) {
    std::vector<ItemSource*> itemSources;
    std::vector<ItemSink*> itemSinks;
    
    for(GridObject* cur : grid.allGridObjects()) {
        ItemSource* asSource = dynamic_cast<ItemSource*>(cur);
        if(asSource != nullptr) {
            itemSources.push_back(asSource);
        }

        ItemSink* asSink = dynamic_cast<ItemSink*>(cur);
        if(asSink != nullptr) {
            itemSinks.push_back(asSink);
        }
    }

    for(ItemSink* curSink : itemSinks) {
        curSink->resetFlowAmounts();
    }

    for(ItemSource* curSource : itemSources) {
        curSource->propagateFlow(nullptr, true);
        curSource->propagateFlow(nullptr, false);
    }
}
