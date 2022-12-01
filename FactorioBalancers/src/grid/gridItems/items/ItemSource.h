#pragma once

#include "../GridItem.h"

class ItemSource : public GridItem {
public:
    ItemSource(const Grid& grid, int row, int col);
protected:
    virtual AsciiImage getImage() const;
};
