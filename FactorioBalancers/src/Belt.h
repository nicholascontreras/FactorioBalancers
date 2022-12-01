#pragma once
#include "GridItem.h"

class Belt : public GridItem {
public:
    Belt(const Grid& grid, int row, int col, Direction direction);
protected:
    virtual AsciiImage getImage() const;
private:
    Direction determineInputDirection() const;
};
