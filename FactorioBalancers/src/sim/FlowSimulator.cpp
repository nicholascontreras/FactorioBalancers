#include "FlowSimulator.h"

#include <vector>
#include <algorithm>

#include "../grid/gridObjects/Splitter.h"

void FlowSimulator::runSimulation(const Grid& grid, int numTestItems, std::vector<ItemSource*> enabledSources, std::vector<ItemSink*> enabledSinks) {
    std::vector<GridObject*> allWithoutDisabled = grid.allGridObjects();
    allWithoutDisabled.erase(std::remove_if(allWithoutDisabled.begin(), allWithoutDisabled.end(), [ & ](GridObject* cur) {
        if(ItemSource* asSource = dynamic_cast<ItemSource*>(cur)) {
            return std::find(enabledSources.begin(), enabledSources.end(), asSource) == enabledSources.end();
        }
        if(ItemSink* asSink = dynamic_cast<ItemSink*>(cur)) {
            return std::find(enabledSinks.begin(), enabledSinks.end(), asSink) == enabledSinks.end();
        }
        return false;
    }), allWithoutDisabled.end());
    
    // Reset simulation
    for(GridObject* cur : grid.allGridObjects()) {
        cur->clearSimulationCounters();
        if(Splitter* curAsSplitter = dynamic_cast<Splitter*>(cur)) {
            curAsSplitter->resetOutputSides();
        }
    }

    // Prime system with items
    for(int i = 0; i < numTestItems; i++) {
        for(GridObject* cur : allWithoutDisabled) {
            cur->advanceLanes();
        }
        for(GridObject* cur : allWithoutDisabled) {
            cur->acceptIncomingItems();
        }
    }

    // Clear stats from priming
    for(GridObject* cur : allWithoutDisabled) {
        if(ItemSource* curAsSource = dynamic_cast<ItemSource*>(cur)) {
            curAsSource->clearSimulationCounters();
        }
        if(ItemSink* curAsSink = dynamic_cast<ItemSink*>(cur)) {
            curAsSink->clearSimulationCounters();
        }
    }

    // Run data leg of simulation 
    for(int i = 0; i < numTestItems; i++) {
        for(GridObject* cur : allWithoutDisabled) {
            cur->advanceLanes();
        }
        for(GridObject* cur : allWithoutDisabled) {
            cur->acceptIncomingItems();
        }
    }

    // Allow Sinks to suck items deposited to them on the last sim step into their counts
    for(GridObject* cur : allWithoutDisabled) {
        if(ItemSink* curAsSink = dynamic_cast<ItemSink*>(cur)) {
            curAsSink->advanceLanes();
        }
    }
}

void FlowSimulator::stepSimulation(const Grid& grid) {
    for(GridObject* cur : grid.allGridObjects()) {
        cur->advanceLanes();
    }
    for(GridObject* cur : grid.allGridObjects()) {
        cur->acceptIncomingItems();
    }
}

void FlowSimulator::resetSimulation(const Grid& grid) {
    for(GridObject* cur : grid.allGridObjects()) {
        cur->clearSimulationCounters();
        if(Splitter* curAsSplitter = dynamic_cast<Splitter*>(cur)) {
            curAsSplitter->resetOutputSides();
        }
    }
}
