#pragma once

#include "GridItem.h"

class Underground : public GridItem {
public:
    Underground(const Grid& grid, int row, int col, Direction direction, bool down);
protected:
    virtual AsciiImage getImage() const;
private:
    const bool down;
};
