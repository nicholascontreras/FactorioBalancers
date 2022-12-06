#include <iostream>

#include "grid/Grid.h"
#include "grid/gridObjects/Belt.h"
#include "grid/gridObjects/Splitter.h"
#include "grid/gridObjects/Underground.h"
#include "grid/gridObjects/items/ItemSource.h"
#include "grid/gridObjects/items/ItemSink.h"

#include "util/Fraction.h"

#include "LayoutBrowser.h"

int main() {
    Grid grid(10, 5);
    grid.addGridObject(new ItemSource(grid, 0, 0));
    grid.addGridObject(new Belt(grid, 0, 1, Direction::EAST));
    grid.addGridObject(new Belt(grid, 0, 2, Direction::SOUTH));
    grid.addGridObject(new Splitter(grid, 1, 2, Direction::SOUTH, false));
    grid.addGridObject(new Splitter(grid, 1, 3, Direction::SOUTH, true));
    grid.addGridObject(new Belt(grid, 2, 2, Direction::SOUTH));
    grid.addGridObject(new Belt(grid, 2, 3, Direction::EAST));
    grid.addGridObject(new Belt(grid, 2, 4, Direction::NORTH));
    grid.addGridObject(new Belt(grid, 1, 4, Direction::NORTH));
    grid.addGridObject(new Belt(grid, 0, 4, Direction::WEST));
    grid.addGridObject(new Belt(grid, 0, 3, Direction::SOUTH));

    grid.addGridObject(new Underground(grid, 3, 2, Direction::EAST, true));
    grid.addGridObject(new Underground(grid, 3, 3, Direction::EAST, false));
    grid.addGridObject(new ItemSink(grid, 3, 4));

    LayoutBrowser::browseLayout(grid);

    return 0;
}