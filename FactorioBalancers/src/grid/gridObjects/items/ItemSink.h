#pragma once

#include "../GridObject.h"

class ItemSink : public GridObject {
public:
    ItemSink(const Grid& grid, int row, int col);

    virtual bool flowCanEnter(Direction incomingFlowDirection, Lane lane) const;
    virtual Lane flowEntersLane(Direction incomingFlowDirection, Lane lane) const;
    virtual bool flowHasPathToSink(Lane lane, std::vector<std::pair<const GridObject*, Lane>> visited = std::vector<std::pair<const GridObject*, Lane>>()) const;
    
    virtual void advanceLanes();

    virtual std::string selectedString() const;
protected:
    virtual AsciiImage getImage() const;
};
