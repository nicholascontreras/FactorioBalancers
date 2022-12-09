#include "LayoutBrowser.h"

#include <conio.h>
#include <iostream>
#include <string>

#include "sim/LayoutTester.h"
#include "sim/FlowSimulator.h"
#include "grid/gridObjects/GridObject.h"

int LayoutBrowser::selectedRow = 0, LayoutBrowser::selectedCol = 0;
bool LayoutBrowser::close = false;
bool LayoutBrowser::runTests = false;
bool LayoutBrowser::runStep = false;
bool LayoutBrowser::resetSim = false;
std::string LayoutBrowser::testResults = "";

void LayoutBrowser::browseLayout(const Grid& grid) {

    std::string clear;
    for(int i = 0; i < 100; i++) {
        clear += "\r\n";
    }

    while(true) {
        if(close) {
            break;
        } else if(runTests) {
            runTests = false;
            testResults = LayoutTester::testLayout(grid);
        } else if(runStep) {
            runStep = false;
            FlowSimulator::stepSimulation(grid);
        } else if(resetSim) {
            resetSim = false;
            FlowSimulator::resetSimulation(grid);
        }

        std::cout << clear << std::endl;
        std::cout << testResults << std::endl;
        std::cout << grid.draw().toString() << std::endl;
        std::cout << "Row: " << selectedRow << " Col: " << selectedCol << std::endl;

        if(grid.isGridObjectAt(selectedRow, selectedCol)) {
            std::cout << grid.gridObjectAt(selectedRow, selectedCol)->selectedString() << std::endl;
        } else {
            std::cout << std::endl;
        }

        waitForKey();
        if(selectedRow < 0) {
            selectedRow = 0;
        } else if(selectedRow >= grid.numRows) {
            selectedRow = grid.numRows - 1;
        }
        if(selectedCol < 0) {
            selectedCol = 0;
        } else if(selectedCol >= grid.numCols) {
            selectedCol = grid.numCols - 1;
        }
    }
}

void LayoutBrowser::waitForKey() {
    int c = _getch();
    if(c == 0 || c == 224) {
        int ex = _getch();
        switch(ex) {
        case 72: // Up
            selectedRow--;
            break;
        case 75: // Left
            selectedCol--;
            break;
        case 77: // Right
            selectedCol++;
            break;
        case 80: // Down
            selectedRow++;
            break;
        }
    } else if (c == 27) {
        close = true;
    } else if(c == 't') {
        runTests = true;
    } else if(c == 's') {
        runStep = true;
    } else if(c == 'r') {
        resetSim = true;
    }
}
