#pragma once

#include <string>

#include "../Grid.h"
#include "../../util/Direction.h"
#include "../../asciiDrawing/AsciiImage.h"
#include "../../asciiDrawing/AsciiCanvas.h"

#include "../../util/Fraction.h"
#include "../../util/util.h"

class GridObject {
public:
    GridObject(const Grid& grid, int row, int col, Direction direction);
    virtual ~GridObject();

    inline int getRow() const { return row; };
    inline int getCol() const { return col; };
    inline Direction getDirection() const { return direction; };

    void draw(AsciiCanvas& canvas) const;

    virtual bool flowCanEnter(Direction incomingFlowDirection, bool leftLane) const = 0;
    virtual bool flowEntersLeftLane(Direction incomingFlowDirection, bool leftLane) const = 0;;
    virtual bool flowHasPathToSink(bool leftLane, std::vector<const GridObject*> visited) const = 0;

    struct FlowRecord {
        FlowRecord* prev;
        Fraction amount;
        const GridObject* gridObject;
        bool leftLane;

        FlowRecord(const FlowRecord* other);
        FlowRecord(FlowRecord* prev, Fraction amount, const GridObject* gridObject, bool leftLane);

        FlowRecord* recordContains(GridObject* go, bool leftLane);
        void deleteRecords();
    };

    virtual void propagateFlow(FlowRecord* flowRecord, bool leftLane) const = 0;

    virtual std::string selectedString() const = 0;
protected:
    const Grid& grid;

    virtual AsciiImage getImage() const = 0;
private:
    const int row, col;
    const Direction direction;
};
