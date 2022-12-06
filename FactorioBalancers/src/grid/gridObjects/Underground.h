#pragma once

#include "GridObject.h"

class Underground : public GridObject {
public:
    Underground(const Grid& grid, int row, int col, Direction direction, bool down);
    virtual bool flowCanEnter(Direction incomingFlowDirection, bool leftLane) const;
    virtual bool flowEntersLeftLane(Direction incomingFlowDirection, bool leftLane) const;
    virtual bool flowHasPathToSink(bool leftLane, std::vector<const GridObject*> visited) const;
    virtual void propagateFlow(FlowRecord* flowRecord, bool leftLane) const;
    virtual std::string selectedString() const;
protected:
    virtual AsciiImage getImage() const;
private:
    const bool down;

    const Underground* getOtherHalf() const;
};
