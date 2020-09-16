#pragma once

#include <array>
#include <string>

class Board {
private:
    void drawHorizontalLine();
public:
    static constexpr int  BOARD_SIZE = 10; // Max value is 26. If greater, change drawBoard
protected:
    std::array<std::array<std::string, BOARD_SIZE>, BOARD_SIZE> board; // string as "   ", three characters
public:
    Board();
    void drawBoard();
};