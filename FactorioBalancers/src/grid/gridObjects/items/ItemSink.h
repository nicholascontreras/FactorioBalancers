#pragma once

#include "../GridObject.h"

class ItemSink : public GridObject {
public:
    ItemSink(const Grid& grid, int row, int col);
    virtual bool flowCanEnter(Direction incomingFlowDirection, bool leftLane) const;
    virtual bool flowEntersLeftLane(Direction incomingFlowDirection, bool leftLane) const;
    virtual bool flowHasPathToSink(bool leftLane, std::vector<const GridObject*> visited) const;
    virtual void propagateFlow(FlowRecord* flowRecord, bool leftLane) const;
    void resetFlowAmounts();
    virtual std::string selectedString() const;
protected:
    virtual AsciiImage getImage() const;
private:
    mutable Fraction flowLeftLane, flowRightLane;
};
