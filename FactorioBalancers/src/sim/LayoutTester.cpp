#include "LayoutTester.h"

#include <algorithm>

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

    results += "Throughput: ";
    if(!stopTests) {
        std::string throughputResult = testIsThroughputUnlimited(grid);
        if(throughputResult.empty()) {
            results += "PASS\r\n";
        } else {
            results += "FAIL: " + throughputResult + "\r\n";
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
        if(!curSource->flowHasPathToSink(GridObject::Lane::LEFT)) {
            return "Source at (" + std::to_string(curSource->getRow()) + "," + std::to_string(curSource->getCol()) +
                "), Left Lane has no path to Sink.";
        }
        if(!curSource->flowHasPathToSink(GridObject::Lane::RIGHT)) {
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

        int avgItemsPerSink = 0;
        for(ItemSink* curSink : itemSinks) {
            const GridObject::SimulationRecord* record = curSink->getSimulationRecord();
            avgItemsPerSink += record->exportsLeftLane;
            avgItemsPerSink += record->exportsRightLane;
        }
        avgItemsPerSink /= (int)itemSinks.size();

        for(ItemSink* curSink : itemSinks) {
            const GridObject::SimulationRecord* record = curSink->getSimulationRecord();
            int curNumItems = record->exportsLeftLane + record->exportsRightLane;
            if(std::abs(avgItemsPerSink - curNumItems) > 1) {
                return "Sink at (" + std::to_string(curSink->getRow()) + "," + std::to_string(curSink->getCol()) +
                    "), expected " + std::to_string(avgItemsPerSink / 2) + "% flow, got " + std::to_string(curNumItems / 2) + "%.";
            }
        }
    }

    return "";
}

std::string LayoutTester::testIsThroughputUnlimited(const Grid& grid) {
    std::vector<ItemSource*> itemSources = allSources(grid);
    std::vector<ItemSink*> itemSinks = allSinks(grid);

    std::vector<std::vector<ItemSource*>> sourceSubsets = subsets(itemSources);
    std::vector<std::vector<ItemSink*>> sinkSubsets = subsets(itemSinks);

    for(std::vector<ItemSource*> curSourceSubset : sourceSubsets) {
        for(std::vector<ItemSink*> curSinkSubset : sinkSubsets) {
            int numSources = (int)curSourceSubset.size();
            int numSinks = (int)curSinkSubset.size();

            FlowSimulator::runSimulation(grid, 100, curSourceSubset, curSinkSubset);

            int expectedItemsPerSink = std::min((100 * numSources) / numSinks, 100) * 2;

            for(ItemSink* curSink : curSinkSubset) {
                const GridObject::SimulationRecord* record = curSink->getSimulationRecord();
                int curNumItems = record->exportsLeftLane + record->exportsRightLane;

                if(std::abs(expectedItemsPerSink - curNumItems) > 1) {
                    return "Sink at (" + std::to_string(curSink->getRow()) + "," + std::to_string(curSink->getCol()) +
                        "), expected " + std::to_string(expectedItemsPerSink / 2) + "% flow, got " + std::to_string(curNumItems / 2) + "%.";
                }
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