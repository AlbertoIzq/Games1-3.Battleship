#include "GuessBoard.h"

GuessBoard::GuessBoard() {
    // Initialize guess_board
    for (int i{ 0 }; i < BOARD_SIZE; ++i) {
        guess_board.at(i).fill(Cell_Type_Guess_Board::CT_NONE);
    }
}

// GET METHODS
std::array<std::array<Cell_Type_Guess_Board, Board::BOARD_SIZE>, Board::BOARD_SIZE>& GuessBoard::getGuessBoard() { return guess_board; }

// SET METHODS
void GuessBoard::setGuessBoard(Position& pos, Cell_Type_Guess_Board type) {
    guess_board.at(pos.row - 1).at(pos.col - 1) = type; // - 1 because array is 0-indexed
    board.at(pos.row - 1).at(pos.col - 1) = cell_types.at(type); // Set board cell with corresponding std::string
}