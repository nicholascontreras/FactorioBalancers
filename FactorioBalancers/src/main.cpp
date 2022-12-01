#include <iostream>

#include "grid/Grid.h"
#include "grid/gridItems/Belt.h"
#include "grid/gridItems/Splitter.h"
#include "grid/gridItems/Underground.h"
#include "grid/gridItems/items/ItemSource.h"
#include "grid/gridItems/items/ItemSink.h"

#include "util/Fraction.h"

int main() {
    Grid grid;
    grid.addGridItem(new ItemSource(grid, 0, 0));
    grid.addGridItem(new Belt(grid, 0, 1, Direction::EAST));
    grid.addGridItem(new Belt(grid, 0, 2, Direction::SOUTH));
    grid.addGridItem(new Splitter(grid, 1, 2, Direction::SOUTH, false));
    grid.addGridItem(new Splitter(grid, 1, 3, Direction::SOUTH, true));
    grid.addGridItem(new Belt(grid, 2, 3, Direction::SOUTH));
    grid.addGridItem(new Belt(grid, 3, 3, Direction::EAST));
    grid.addGridItem(new ItemSink(grid, 3, 4));

    std::cout << grid.draw().toString() << std::endl;

    return 0;
}