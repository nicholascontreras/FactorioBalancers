#pragma once

#include <string>

#include "../Grid.h"
#include "../../util/Direction.h"
#include "../../asciiDrawing/AsciiImage.h"
#include "../../asciiDrawing/AsciiCanvas.h"

class GridItem {
public:
    GridItem(const Grid& grid, int row, int col, Direction direction);
    virtual ~GridItem();

    inline int getRow() const { return row; };
    inline int getCol() const { return col; };
    inline Direction getDirection() const { return direction; };

    void draw(AsciiCanvas& canvas) const;
protected:
    const Grid& grid;

    virtual AsciiImage getImage() const = 0;
private:
    const int row, col;
    const Direction direction;
};
