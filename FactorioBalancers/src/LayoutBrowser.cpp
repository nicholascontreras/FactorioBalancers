#include "LayoutBrowser.h"

#include <conio.h>
#include <iostream>
#include <string>

#include "sim/FlowSimulator.h"
#include "grid/gridObjects/GridObject.h"

int LayoutBrowser::selectedRow = 0, LayoutBrowser::selectedCol = 0;
bool LayoutBrowser::runSim = false;

void LayoutBrowser::browseLayout(const Grid& grid) {

    std::string clear;
    for(int i = 0; i < 100; i++) {
        clear += "\r\n";
    }

    while(true) {

        if(runSim) {
            runSim = false;
            FlowSimulator::runSimulation(grid);
        }

        std::cout << clear << std::endl;
        std::cout << grid.draw().toString() << std::endl;
        std::cout << "Row: " << selectedRow << " Col: " << selectedCol << std::endl;

        if(grid.isGridObjectAt(selectedRow, selectedCol)) {
            std::cout << grid.gridObjectAt(selectedRow, selectedCol)->selectedString() << std::endl;
        } else {
            std::cout << std::endl;
        }

        waitForKey();
    }
}

void LayoutBrowser::waitForKey() {
    int c = _getch();
    if(c == 0 || c == 224) {
        int ex = _getch();
        switch(ex) {
        case 72: /* Up */
            selectedRow--;
            break;
        case 75: /* Left */
            selectedCol--;
            break;
        case 77: /* Right */
            selectedCol++;
            break;
        case 80: /* Down */
            selectedRow++;
            break;
        }

        if(selectedRow < 0) {
            selectedRow = 0;
        }
        if(selectedCol < 0) {
            selectedCol = 0;
        }

    } else if(c == 'r') {
        runSim = true;
    }
}
