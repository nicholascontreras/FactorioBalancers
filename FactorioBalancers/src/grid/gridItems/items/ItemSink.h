#pragma once

#include "../GridItem.h"

class ItemSink : public GridItem {
public:
    ItemSink(const Grid& grid, int row, int col);
protected:
    virtual AsciiImage getImage() const;
};
