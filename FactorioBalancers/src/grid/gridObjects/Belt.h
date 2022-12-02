#pragma once
#include "GridObject.h"

class Belt : public GridObject {
public:
    Belt(const Grid& grid, int row, int col, Direction direction);
    virtual bool flowCanEnter(Direction incomingFlowDirection, bool leftLane) const;
    virtual bool flowEntersLeftLane(Direction incomingFlowDirection, bool leftLane) const;
    virtual bool flowHasPathToSink(bool leftLane, std::vector<const GridObject*> visited) const;
    virtual std::string selectedString() const;
protected:
    virtual void propagateFlow(FlowRecord* flowRecord, bool leftLane) const;
    virtual AsciiImage getImage() const;
private:
    Direction determineInputDirection() const;
};
