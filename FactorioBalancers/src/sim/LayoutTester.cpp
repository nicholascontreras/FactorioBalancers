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
        FlowSimulator::runSimulation(grid, 100, curSourceSubset, itemSinks);

        int sumOfItemsLeftLane = 0;
        int sumOfItemsRightLane = 0;
        int numSinks = 0;

        for(ItemSink* curSink : itemSinks) {
            const GridObject::SimulationRecord* record = curSink->getSimulationRecord();
            if(numSinks > 0) {
                int avgItemsLeftLane = sumOfItemsLeftLane / numSinks;
                int avgItemsRightLane = sumOfItemsRightLane / numSinks;

                if(std::abs(record->exportsLeftLane - avgItemsLeftLane) > 1) {
                    return "Sink at (" + std::to_string(curSink->getRow()) + "," + std::to_string(curSink->getCol()) +
                        "), Left Lane expected " + std::to_string(avgItemsLeftLane) + "% flow, got " + std::to_string(record->exportsLeftLane) + "%.";
                }
                if(std::abs(record->exportsRightLane - avgItemsRightLane) > 1) {
                    return "Sink at (" + std::to_string(curSink->getRow()) + "," + std::to_string(curSink->getCol()) +
                        "), Right Lane expected " + std::to_string(avgItemsRightLane) + "% flow, got " + std::to_string(record->exportsRightLane) + "%.";
                }
            }

            sumOfItemsLeftLane += record->exportsLeftLane;
            sumOfItemsRightLane += record->exportsRightLane;
            numSinks++;
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