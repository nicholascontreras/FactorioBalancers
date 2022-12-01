#include "AsciiImage.h"

#include <algorithm>
#include <stdexcept>

AsciiImage::AsciiImage(std::initializer_list<std::string> rows) {
    int expectedWidth = (int) rows.begin()->size();

    for(std::string curRow : rows) {
        if(curRow.size() == expectedWidth) {
            image.push_back(curRow);
        } else {
            throw std::invalid_argument("Image must be rectangular!");
        }
    }

    insert437();
}

int AsciiImage::getWidth() const {
    return (int)image.at(0).size();
}

int AsciiImage::getHeight() const {
    return (int)image.size();
}

char AsciiImage::at(int x, int y) const {
    if(x >= 0 && x < getWidth() && y >= 0 && y < getHeight()) {
        return image.at(y).at(x);
    } else {
        throw std::invalid_argument("Given position is outside dimensions of the image!");
    }
}

void AsciiImage::insert437() {
    for(std::string& curLine : image) {
        std::replace(curLine.begin(), curLine.end(), '0', '\xBF'); // ┐
        std::replace(curLine.begin(), curLine.end(), '1', '\xC0'); // └
        std::replace(curLine.begin(), curLine.end(), '2', '\xD9'); // ┘
        std::replace(curLine.begin(), curLine.end(), '3', '\xDA'); // ┌
    }
}
