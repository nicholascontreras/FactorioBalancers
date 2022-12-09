#pragma once

#include "GridObject.h"

class Underground : public GridObject {
public:
    Underground(const Grid& grid, int row, int col, Direction direction, bool down);
    virtual bool flowCanEnter(Direction incomingFlowDirection, Lane lane) const;
    virtual Lane flowEntersLane(Direction incomingFlowDirection, Lane lane) const;
    virtual bool flowHasPathToSink(Lane lane, std::vector<const GridObject*> visited) const;

    virtual void advanceLanes();

    bool isDown() const;
    virtual std::string selectedString() const;
protected:
    virtual AsciiImage getImage() const;
private:
    const bool down;

    Underground* getOtherHalf() const;
};
