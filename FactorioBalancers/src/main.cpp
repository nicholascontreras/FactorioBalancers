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
    grid.addGridObject(new ItemSource(grid, 2, 0));
    //grid.addGridObject(new ItemSource(grid, 3, 0));

    grid.addGridObject(new Splitter(grid, 0, 1, Direction::EAST, Splitter::SplitterSide::LEFT));
    grid.addGridObject(new Splitter(grid, 1, 1, Direction::EAST, Splitter::SplitterSide::RIGHT));
    grid.addGridObject(new Splitter(grid, 2, 1, Direction::EAST, Splitter::SplitterSide::LEFT));
    grid.addGridObject(new Splitter(grid, 3, 1, Direction::EAST, Splitter::SplitterSide::RIGHT));

    // BEGIN "simple TL 4x4"
    //grid.addGridObject(new Splitter(grid, 1, 2, Direction::EAST, Splitter::SplitterSide::LEFT));
    //grid.addGridObject(new Splitter(grid, 2, 2, Direction::EAST, Splitter::SplitterSide::RIGHT));

    //grid.addGridObject(new Belt(grid, 1, 3, Direction::EAST));

    //grid.addGridObject(new Splitter(grid, 1, 4, Direction::EAST, Splitter::SplitterSide::LEFT));
    //grid.addGridObject(new Splitter(grid, 2, 4, Direction::EAST, Splitter::SplitterSide::RIGHT));

    //grid.addGridObject(new Splitter(grid, 0, 5, Direction::EAST, Splitter::SplitterSide::LEFT));
    //grid.addGridObject(new Splitter(grid, 1, 5, Direction::EAST, Splitter::SplitterSide::RIGHT));
    //grid.addGridObject(new Splitter(grid, 2, 5, Direction::EAST, Splitter::SplitterSide::LEFT));
    //grid.addGridObject(new Splitter(grid, 3, 5, Direction::EAST, Splitter::SplitterSide::RIGHT));

    //grid.addGridObject(new ItemSink(grid, 0, 6));
    //grid.addGridObject(new ItemSink(grid, 1, 6));
    //grid.addGridObject(new ItemSink(grid, 2, 6));
    //grid.addGridObject(new ItemSink(grid, 3, 6));
    // END "simple TL 4x4"

    // BEGIN "classic TU 4x4"
    grid.addGridObject(new Belt(grid, 0, 2, Direction::EAST));
    grid.addGridObject(new Splitter(grid, 1, 2, Direction::EAST, Splitter::SplitterSide::LEFT));
    grid.addGridObject(new Splitter(grid, 2, 2, Direction::EAST, Splitter::SplitterSide::RIGHT));
    grid.addGridObject(new Belt(grid, 3, 2, Direction::EAST));

    grid.addGridObject(new Belt(grid, 0, 3, Direction::EAST));
    grid.addGridObject(new Underground(grid, 1, 3, Direction::EAST, true));
    grid.addGridObject(new Underground(grid, 2, 3, Direction::EAST, true));
    grid.addGridObject(new Belt(grid, 3, 3, Direction::EAST));

    grid.addGridObject(new Belt(grid, 0, 4, Direction::SOUTH));
    grid.addGridObject(new Belt(grid, 1, 4, Direction::EAST));
    grid.addGridObject(new Belt(grid, 2, 4, Direction::EAST));
    grid.addGridObject(new Belt(grid, 3, 4, Direction::NORTH));

    grid.addGridObject(new Splitter(grid, 1, 5, Direction::EAST, Splitter::SplitterSide::LEFT));
    grid.addGridObject(new Splitter(grid, 2, 5, Direction::EAST, Splitter::SplitterSide::RIGHT));

    grid.addGridObject(new Belt(grid, 0, 6, Direction::EAST));
    grid.addGridObject(new Belt(grid, 1, 6, Direction::NORTH));
    grid.addGridObject(new Belt(grid, 2, 6, Direction::SOUTH));
    grid.addGridObject(new Belt(grid, 3, 6, Direction::EAST));

    grid.addGridObject(new Belt(grid, 0, 7, Direction::EAST));
    grid.addGridObject(new Underground(grid, 1, 7, Direction::EAST, false));
    grid.addGridObject(new Underground(grid, 2, 7, Direction::EAST, false));
    grid.addGridObject(new Belt(grid, 3, 7, Direction::EAST));

    grid.addGridObject(new Splitter(grid, 0, 8, Direction::EAST, Splitter::SplitterSide::LEFT));
    grid.addGridObject(new Splitter(grid, 1, 8, Direction::EAST, Splitter::SplitterSide::RIGHT));
    grid.addGridObject(new Splitter(grid, 2, 8, Direction::EAST, Splitter::SplitterSide::LEFT));
    grid.addGridObject(new Splitter(grid, 3, 8, Direction::EAST, Splitter::SplitterSide::RIGHT));

    grid.addGridObject(new ItemSink(grid, 0, 9));
    grid.addGridObject(new ItemSink(grid, 1, 9));
    grid.addGridObject(new ItemSink(grid, 2, 9));
    //grid.addGridObject(new ItemSink(grid, 3, 9));
    // END "classic TU 4x4"

    //3x3 loopback
    grid.addGridObject(new Belt(grid, 3, 9, Direction::SOUTH));
    grid.addGridObject(new Belt(grid, 4, 9, Direction::WEST));
    grid.addGridObject(new Belt(grid, 4, 8, Direction::WEST));
    grid.addGridObject(new Belt(grid, 4, 7, Direction::WEST));
    grid.addGridObject(new Belt(grid, 4, 6, Direction::WEST));
    grid.addGridObject(new Belt(grid, 4, 5, Direction::WEST));
    grid.addGridObject(new Belt(grid, 4, 4, Direction::WEST));
    grid.addGridObject(new Belt(grid, 4, 3, Direction::WEST));
    grid.addGridObject(new Belt(grid, 4, 2, Direction::WEST));
    grid.addGridObject(new Belt(grid, 4, 1, Direction::WEST));
    grid.addGridObject(new Belt(grid, 4, 0, Direction::NORTH));
    grid.addGridObject(new Belt(grid, 3, 0, Direction::EAST));

    LayoutBrowser::browseLayout(grid);

    return 0;
}