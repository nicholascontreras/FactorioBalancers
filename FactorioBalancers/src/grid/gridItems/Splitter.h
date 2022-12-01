#pragma once

#include "GridItem.h"

class Splitter : public GridItem {
public:
    Splitter(const Grid& grid, int row, int col, Direction direction, bool leftHalf);
protected:
    virtual AsciiImage getImage() const;
private:
    const bool leftHalf;
};