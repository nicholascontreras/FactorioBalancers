#pragma once

#include "grid/Grid.h"
#include "util/Direction.h"

class LayoutBrowser {
public:
    static void browseLayout(const Grid& grid);

private:
    static int selectedRow, selectedCol;
    static bool close;
    static bool runTests;
    static bool runStep;
    static bool resetSim;
    static std::string testResults;

    static void waitForKey();

};
