#pragma once
#include <vector>

#include "../asciiDrawing/AsciiCanvas.h"

// Forward declare GridObject
class GridObject;

class Grid {
public:
    Grid();
    ~Grid();

    Grid(const Grid& other) = delete;
    Grid& operator=(const Grid& other) = delete;

    bool isGridObjectAt(int row, int col) const;
    const GridObject* gridObjectAt(int row, int col) const;

    void addGridItem(GridObject* gridItem);

    const std::vector<GridObject*> allGridObjects() const;

    AsciiCanvas draw() const;
private:
    std::vector<GridObject*> gridItems;
};