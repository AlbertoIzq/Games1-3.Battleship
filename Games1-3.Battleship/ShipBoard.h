#pragma once
#include "Board.h"
#include "Ship.h"

#include <map>
#include <string>

enum class Cell_Type_Ship_Board
{
    CT_NONE, // "   "
    CT_MISSED, // " X "
    CT_AIRCRAFT_CARRIER, // " A "
    CT_BATTLESHIP, // " B "
    CT_CRUISER, // " C "
    CT_DESTROYER, // " D "
    CT_SUBMARINE, // " S "
    CT_AIRCRAFT_CARRIER_HIT, // "*A*"
    CT_BATTLESHIP_HIT, // "*B*"
    CT_CRUISER_HIT, // "*C*"
    CT_DESTROYER_HIT, // "*D*"
    CT_SUBMARINE_HIT, // "*S*"
};

class ShipBoard : public Board {
private:
    static constexpr int NUM_SHIPS = 5;
    std::map<Cell_Type_Ship_Board, std::string> cell_types{
        std::make_pair(Cell_Type_Ship_Board::CT_NONE, "   "),
        std::make_pair(Cell_Type_Ship_Board::CT_MISSED, " X "),
        std::make_pair(Cell_Type_Ship_Board::CT_AIRCRAFT_CARRIER, " A "),
        std::make_pair(Cell_Type_Ship_Board::CT_BATTLESHIP, " B "),
        std::make_pair(Cell_Type_Ship_Board::CT_CRUISER, " C "),
        std::make_pair(Cell_Type_Ship_Board::CT_DESTROYER, " D "),
        std::make_pair(Cell_Type_Ship_Board::CT_SUBMARINE, " S "),
        std::make_pair(Cell_Type_Ship_Board::CT_AIRCRAFT_CARRIER_HIT, "*A*"),
        std::make_pair(Cell_Type_Ship_Board::CT_BATTLESHIP_HIT, "*B*"),
        std::make_pair(Cell_Type_Ship_Board::CT_CRUISER_HIT, "*C*"),
        std::make_pair(Cell_Type_Ship_Board::CT_DESTROYER_HIT, "*D*"),
        std::make_pair(Cell_Type_Ship_Board::CT_SUBMARINE_HIT, "*S*")
    };

    bool isValidPlacement(Ship&);
    bool ShipOverlapsAnotherShipCol(Ship&, const int&);
    bool ShipOverlapsAnotherShipRow(Ship&, const int&);
    void placeShipOnShipBoard(Ship&);
    void iniUpdateBoard();
protected:
    std::array<Ship, NUM_SHIPS> ships;
    std::array<std::array<Cell_Type_Ship_Board, BOARD_SIZE>, BOARD_SIZE> ship_board;

public:
    ShipBoard();
    void inisetShipBoard();

    // GET METHODS
    std::array<Ship, NUM_SHIPS>& getShips();
    std::array<std::array<Cell_Type_Ship_Board, BOARD_SIZE>, BOARD_SIZE>& getShipBoard();

    // SET METHODS
    void setShipBoard(Position&, Cell_Type_Ship_Board);
    void setShips(Position&, Cell_Type_Ship_Board);
};