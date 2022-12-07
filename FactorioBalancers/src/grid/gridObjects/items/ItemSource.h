#pragma once

#include "../GridObject.h"

class ItemSource : public GridObject {
public:
    ItemSource(const Grid& grid, int row, int col);

    virtual bool flowCanEnter(Direction incomingFlowDirection, Lane lane) const;
    virtual Lane flowEntersLane(Direction incomingFlowDirection, Lane lane) const;
    virtual bool flowHasPathToSink(Lane lane, std::vector<const GridObject*> visited) const;
    
    virtual void advanceLanes();
    
    virtual std::string selectedString() const;
protected:
    virtual AsciiImage getImage() const;
};
