#pragma once
#include <vector>

#include "../asciiDrawing/AsciiCanvas.h"

// Forward declare GridObject
class GridObject;

class Grid {
public:
    const int numRows, numCols;

    Grid(int numRows, int numCols);
    ~Grid();

    Grid(const Grid& other) = delete;
    Grid& operator=(const Grid& other) = delete;

    bool isOnGrid(int row, int col) const;
    bool isGridObjectAt(int row, int col) const;
    GridObject* gridObjectAt(int row, int col) const;

    void addGridObject(GridObject* gridItem);
    void removeGridObject(int row, int col);

    const std::vector<GridObject*> allGridObjects() const;

    AsciiCanvas draw() const;
private:
    std::vector<GridObject*> gridObjects;
};