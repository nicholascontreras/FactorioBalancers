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
    Grid grid;
    grid.addGridItem(new ItemSource(grid, 0, 0));
    grid.addGridItem(new Belt(grid, 0, 1, Direction::EAST));
    grid.addGridItem(new Belt(grid, 0, 2, Direction::SOUTH));
    grid.addGridItem(new Splitter(grid, 1, 2, Direction::SOUTH, false));
    grid.addGridItem(new Splitter(grid, 1, 3, Direction::SOUTH, true));
    grid.addGridItem(new Belt(grid, 2, 2, Direction::SOUTH));
    grid.addGridItem(new Belt(grid, 2, 3, Direction::EAST));
    grid.addGridItem(new Belt(grid, 3, 2, Direction::EAST));
    grid.addGridItem(new Belt(grid, 3, 3, Direction::EAST));
    grid.addGridItem(new ItemSink(grid, 2, 4));
    grid.addGridItem(new ItemSink(grid, 3, 4));

    LayoutBrowser::browseLayout(grid);

    return 0;
}