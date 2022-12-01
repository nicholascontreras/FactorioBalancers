#include "AsciiCanvas.h"

#include <stdexcept>

AsciiCanvas::AsciiCanvas(int width, int height) : width(width), height(height) {
    for(int y = 0; y < height; y++) {
        canvas.push_back(std::vector<char>(width, ' '));
    }
}

void AsciiCanvas::draw(int x, int y, AsciiImage image) {
    if(x < 0 || y < 0) {
        throw std::invalid_argument("Position out of bounds!");
    }
    if(x + image.getWidth() > width || y + image.getHeight() > height) {
        throw std::invalid_argument("Position out of bounds!");
    }

    for(int curY = 0; curY < image.getHeight(); curY++) {
        for(int curX = 0; curX < image.getWidth(); curX++) {
            canvas.at((size_t)y + curY).at((size_t)x + curX) = image.at(curX, curY);
        }
    }
}

std::string AsciiCanvas::toString() const {
    std::string output = std::string((size_t)width + 2, '-') + "\r\n";
    for(int y = 0; y < height; y++) {
        output += "|";
        for(int x = 0; x < width; x++) {
            output += canvas.at(y).at(x);
        }
        output += "|\r\n";
    }
    output += std::string((size_t)width + 2, '-');
    return output;
}
