#pragma once

#include <vector>
#include <string>

#include "AsciiImage.h"

class AsciiCanvas {

public:
    AsciiCanvas(int width, int height);

    void draw(int x, int y, AsciiImage image);
    std::string toString() const;
private:
    const int width, height;
    std::vector<std::vector<char>> canvas;
};