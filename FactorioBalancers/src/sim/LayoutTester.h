#pragma once

#include <string>
#include <vector>

#include "../grid/Grid.h"
#include "../grid/gridObjects/items/ItemSource.h"
#include "../grid/gridObjects/items/ItemSink.h"

class LayoutTester {
public:
    static std::string testLayout(const Grid& grid);

private:
    static std::string testIsConnected(const Grid& grid);
    static std::string testIsBalancer(const Grid& grid);
    static std::string testIsThroughputUnlimited(const Grid& grid);

    static std::vector<ItemSource*> allSources(const Grid& grid);
    static std::vector<ItemSink*> allSinks(const Grid& grid);

    template <class T>
    static std::vector<std::vector<T>> subsets(std::vector<T> set);
};

template<class T>
inline std::vector<std::vector<T>> LayoutTester::subsets(std::vector<T> set) {
    if(set.size() == 0) {
        return std::vector<std::vector<T>>();
    }

    std::vector<std::vector<T>> allSubsets;
    allSubsets.push_back(set);

    for(int i = 0; i < set.size(); i++) {
        std::vector<T> withoutCur = set;
        withoutCur.erase(withoutCur.begin() + i);
        for(std::vector<T> subsetFromCall : subsets(withoutCur)) {
            if(std::find(allSubsets.begin(), allSubsets.end(), subsetFromCall) == allSubsets.end()) {
                allSubsets.push_back(subsetFromCall);
            }
        }
    }

    return allSubsets;
}