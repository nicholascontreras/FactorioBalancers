#pragma once

#include "GridObject.h"

class Splitter : public GridObject {
public:
    enum class SplitterSide { LEFT, RIGHT };

    struct SplitterSimulationRecord : public SimulationRecord {
        SplitterSide leftLaneOutput = SplitterSide::LEFT, rightLaneOutput = SplitterSide::LEFT;
        void toggleOutput(Lane lane);
    };

    Splitter(const Grid& grid, int row, int col, Direction direction, SplitterSide side);
    virtual bool flowCanEnter(Direction incomingFlowDirection, Lane lane) const;
    virtual Lane flowEntersLane(Direction incomingFlowDirection, Lane lane) const;
    virtual bool flowHasPathToSink(Lane lane, std::vector<std::pair<const GridObject*, Lane>> visited = std::vector<std::pair<const GridObject*, Lane>>()) const;

    virtual void advanceLanes();
    virtual void resetOutputSides();

    virtual std::string selectedString() const;
protected:
    virtual AsciiImage getImage() const;
private:
    const SplitterSide side;

    Splitter* getOtherHalf() const;
    SplitterSimulationRecord* getSplitterSimRecord() const;
};