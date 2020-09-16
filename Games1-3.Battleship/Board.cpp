#include "Board.h"

#include <vector>
#include <iostream>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;

Board::Board() {
    // Initialize board
    for (int i{ 0 }; i < BOARD_SIZE; ++i) {
        board.at(i).fill("   ");
    }
}

void Board::drawHorizontalLine() {
    cout << "  +";
    for (int i{ 1 }; i <= BOARD_SIZE; ++i) {
        cout << "---+";
    }
    cout << endl;
}

void Board::drawBoard() {
    std::vector<char> alphabet{ 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

    cout << "    ";
    for (int i{ 1 }; i <= BOARD_SIZE; ++i) {
        if (i < 10)
            cout << i << "   ";
        else
            cout << i << "  ";
    }
    cout << endl;
    drawHorizontalLine();
    for (int i{ 0 }; i < BOARD_SIZE; ++i) {
        cout << alphabet.at(i) << " |";
        for (int j{ 0 }; j < BOARD_SIZE; ++j) {
            cout << board.at(i).at(j) << "|";
        }
        cout << endl;
        drawHorizontalLine();
    }
}

/*
    1   2   3   4   5   6   7   8   9   10
  +---+---+---+---+---+---+---+---+---+---+
A |   |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+
B |   |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+
C |   |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+
D |   |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+
E |   |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+
F |   |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+
G |   |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+
H |   |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+
I |   |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+
J |   |   |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+---+---+
*/