#include "LayoutTester.h"

#include "FlowSimulator.h"

std::string LayoutTester::testLayout(const Grid& grid) {
    std::string results;
    bool stopTests = false;

    results += "Connected: ";
    std::string connectedResult = testIsConnected(grid);
    if(connectedResult.empty()) {
        results += "PASS\r\n";
    } else {
        results += "FAIL: " + connectedResult + "\r\n";
        stopTests = true;
    }

    results += "Balancer: ";
    if(!stopTests) {
        std::string balancerResult = testIsBalancer(grid);
        if(balancerResult.empty()) {
            results += "PASS\r\n";
        } else {
            results += "FAIL: " + balancerResult + "\r\n";
            stopTests = true;
        }
    } else {
        results += "SKIP\r\n";
    }

    return results;
}

std::string LayoutTester::testIsConnected(const Grid& grid) {
    std::vector<ItemSource*> itemSources = allSources(grid);

    for(ItemSource* curSource : itemSources) {
        if(!curSource->flowHasPathToSink(GridObject::Lane::LEFT, std::vector<const GridObject*>())) {
            return "Source at (" + std::to_string(curSource->getRow()) + "," + std::to_string(curSource->getCol()) +
                "), Left Lane has no path to Sink.";
        }
        if(!curSource->flowHasPathToSink(GridObject::Lane::RIGHT, std::vector<const GridObject*>())) {
            return "Source at (" + std::to_string(curSource->getRow()) + "," + std::to_string(curSource->getCol()) +
                "), Right Lane has no path to Sink.";
        }
    }

    return "";
}

std::string LayoutTester::testIsBalancer(const Grid& grid) {
    std::vector<ItemSource*> itemSources = allSources(grid);
    std::vector<ItemSink*> itemSinks = allSinks(grid);

    std::vector<std::vector<ItemSource*>> sourceSubsets = subsets(itemSources);
    for(std::vector<ItemSource*> curSourceSubset : sourceSubsets) {
        int expectedItemsPerSink = 100;
        FlowSimulator::runSimulation(grid, expectedItemsPerSink * (int)itemSinks.size(), curSourceSubset, itemSinks);

        for(ItemSink* curSink : itemSinks) {
            const GridObject::SimulationRecord* record = curSink->getSimulationRecord();
            if(std::abs(record->exportsLeftLane - expectedItemsPerSink) > 1) {
                return "Sink at (" + std::to_string(curSink->getRow()) + "," + std::to_string(curSink->getCol()) +
                    "), Left Lane expected " + std::to_string(expectedItemsPerSink) + " items, got " + std::to_string(record->exportsLeftLane) + ".";
            }
            if(std::abs(record->exportsRightLane - expectedItemsPerSink) > 1) {
                return "Sink at (" + std::to_string(curSink->getRow()) + "," + std::to_string(curSink->getCol()) +
                    "), Right Lane expected " + std::to_string(expectedItemsPerSink) + " items, got " + std::to_string(record->exportsRightLane) + ".";
            }
        }
    }

    return "";
}

std::vector<ItemSource*> LayoutTester::allSources(const Grid& grid) {
    std::vector<ItemSource*> itemSources;

    for(GridObject* cur : grid.allGridObjects()) {
        if(ItemSource* asSource = dynamic_cast<ItemSource*>(cur)) {
            itemSources.push_back(asSource);
        }
    }

    return itemSources;
}

std::vector<ItemSink*> LayoutTester::allSinks(const Grid& grid) {
    std::vector<ItemSink*> itemSinks;

    for(GridObject* cur : grid.allGridObjects()) {
        if(ItemSink* asSink = dynamic_cast<ItemSink*>(cur)) {
            itemSinks.push_back(asSink);
        }
    }

    return itemSinks;
}