#pragma once

#include <initializer_list>
#include <vector>
#include <string>

class AsciiImage {
public:
    AsciiImage(std::initializer_list<std::string> rows);

    int getWidth() const;
    int getHeight() const;

    char at(int x, int y) const;
private:
    std::vector<std::string> image;

    void insert437();
};
