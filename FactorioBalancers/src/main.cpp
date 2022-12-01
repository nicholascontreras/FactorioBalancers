#include <iostream>

#include "Grid.h"
#include "Belt.h"
#include "Splitter.h"

int main() {
    Grid grid;
    grid.addGridItem(new Belt(grid, 1, 1, Direction::NORTH));
    grid.addGridItem(new Belt(grid, 1, 2, Direction::WEST));
    grid.addGridItem(new Splitter(grid, 2, 1, Direction::NORTH, true));
    grid.addGridItem(new Splitter(grid, 2, 2, Direction::NORTH, false));

    std::cout << grid.draw().toString() << std::endl;
    return 0;
}