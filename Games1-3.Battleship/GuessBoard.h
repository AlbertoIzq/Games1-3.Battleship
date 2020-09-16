#pragma once
#include "Board.h"
#include "Ship.h"

#include <map>
#include <string>


enum class Cell_Type_Guess_Board
{
    CT_NONE,
    CT_MISSED, // " X "
    CT_HIT // "* *"
};

class GuessBoard : public Board
{
private:
    std::map<Cell_Type_Guess_Board, std::string> cell_types{
        std::make_pair(Cell_Type_Guess_Board::CT_NONE, "   "),
        std::make_pair(Cell_Type_Guess_Board::CT_MISSED, " X "),
        std::make_pair(Cell_Type_Guess_Board::CT_HIT, "* *"),
    };
protected:
    std::array<std::array<Cell_Type_Guess_Board, BOARD_SIZE>, BOARD_SIZE> guess_board;
public:
    GuessBoard();

    // GET METHODS
    std::array<std::array<Cell_Type_Guess_Board, BOARD_SIZE>, BOARD_SIZE>& getGuessBoard();

    // SET METHODS
    void setGuessBoard(Position&, Cell_Type_Guess_Board);
};

