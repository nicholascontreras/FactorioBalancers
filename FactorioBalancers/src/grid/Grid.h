#pragma once
#include <vector>

#include "../asciiDrawing/AsciiCanvas.h"

// Forward declare GridItem
class GridItem;

class Grid {
public:
    Grid();
    ~Grid();

    Grid(const Grid& other) = delete;
    Grid& operator=(const Grid& other) = delete;

    bool isGridItemAt(int row, int col) const;
    const GridItem* gridItemAt(int row, int col) const;

    void addGridItem(GridItem* gridItem);

    AsciiCanvas draw() const;
private:
    std::vector<GridItem*> gridItems;
};