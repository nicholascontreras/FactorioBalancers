#include <iostream>

#include "grid/Grid.h"
#include "grid/gridObjects/Belt.h"
#include "grid/gridObjects/Splitter.h"
#include "grid/gridObjects/Underground.h"
#include "grid/gridObjects/items/ItemSource.h"
#include "grid/gridObjects/items/ItemSink.h"

#include "LayoutBrowser.h"

int main() {
    Grid grid(5, 10);
    grid.addGridObject(new ItemSource(grid, 0, 0));
    grid.addGridObject(new ItemSource(grid, 1, 0));

    grid.addGridObject(new Splitter(grid, 0, 1, Direction::EAST, Splitter::SplitterSide::LEFT));
    grid.addGridObject(new Splitter(grid, 1, 1, Direction::EAST, Splitter::SplitterSide::RIGHT));

    grid.addGridObject(new Belt(grid, 0, 2, Direction::EAST));
    grid.addGridObject(new ItemSink(grid, 0, 3));
    grid.addGridObject(new ItemSink(grid, 1, 2));

    LayoutBrowser::browseLayout(grid);

    return 0;
}