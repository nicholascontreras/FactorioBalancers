#pragma once

#include <string>
#include <iostream>

#include "../Grid.h"
#include "../../util/Direction.h"
#include "../../asciiDrawing/AsciiImage.h"
#include "../../asciiDrawing/AsciiCanvas.h"

#include "../../util/util.h"

class GridObject {
public:
    static int MAX_ITEMS_PER_LANE;

    struct SimulationRecord {
        int itemsLeftLane = 0, itemsRightLane = 0;
        int incomingItemsLeftLane = 0, incomingItemsRightLane = 0;

        int successfulInsertionsLeftLane = 0, successfulInsertionsRightLane = 0;
        int blockedInsertionsLeftLane = 0, blockedInsertionsRightLane = 0;
        int exportsLeftLane = 0, exportsRightLane = 0;
    };

    enum class Lane { LEFT, RIGHT };

    GridObject(const Grid& grid, int row, int col, Direction direction, SimulationRecord* simulationRecord);
    virtual ~GridObject();

    inline int getRow() const { return row; };
    inline int getCol() const { return col; };
    inline Direction getDirection() const { return direction; };

    void draw(AsciiCanvas& canvas) const;

    virtual bool flowCanEnter(Direction incomingFlowDirection, Lane lane) const = 0;
    virtual Lane flowEntersLane(Direction incomingFlowDirection, Lane lane) const = 0;;
    virtual bool flowHasPathToSink(Lane lane, std::vector<const GridObject*> visited) const = 0;

    void acceptIncomingItems();
    bool receiveItem(Lane lane);
    virtual void advanceLanes() = 0;
    virtual void clearSimulationCounters();
    const SimulationRecord* getSimulationRecord() const;

    virtual std::string selectedString() const = 0;
protected:
    const Grid& grid;

    SimulationRecord* simulationRecord;

    bool laneHasItem(Lane lane);
    bool isLaneFull(Lane lane);

    virtual AsciiImage getImage() const = 0;
private:
    const int row, col;
    const Direction direction;
};
