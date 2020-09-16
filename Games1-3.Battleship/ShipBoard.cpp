#include "ShipBoard.h"
#include "Ship.h"

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

ShipBoard::ShipBoard()
    : ships{Ship(Ship_Type::ST_AIRCRAFT_CARRIER),
            Ship(Ship_Type::ST_BATTLESHIP),
            Ship(Ship_Type::ST_CRUISER),
            Ship(Ship_Type::ST_DESTROYER),
            Ship(Ship_Type::ST_SUBMARINE)} {
    // Initialize ship_board
    for (int i{ 0 }; i < BOARD_SIZE; ++i) {
        ship_board.at(i).fill(Cell_Type_Ship_Board::CT_NONE);
    }
}

bool ShipBoard::isValidPlacement(Ship& ship) {
    bool isValid{ true };
    if (ship.getOrientation() == Ship_Orientation::SO_HORIZONTAL) {
        for (int i{ ship.getPosition().col }; i < ship.getPosition().col + ship.getSize(); ++i) {
            if (ShipOverlapsAnotherShipCol(ship, i) || i > BOARD_SIZE) { // Ship will overlap another ship or the ship will be off horizontally
                isValid = false;
                break;
            }
        }
    }
    else {
        for (int i{ ship.getPosition().row }; i < ship.getPosition().row + ship.getSize(); ++i) {
            if (ShipOverlapsAnotherShipRow(ship, i) || i > BOARD_SIZE) { // Ship will overlap another ship or the ship will be off vertically
                isValid = false;
                break;
            }
        }
    }
    return isValid;
}

bool ShipBoard::ShipOverlapsAnotherShipCol(Ship& ship, const int& col) {
    bool overlaps{ false };
    for (Ship& s : ships) {
        if (&s == &ship) // If it's the same ship, skip it
            continue;
        if (s.getOrientation() == Ship_Orientation::SO_HORIZONTAL) {
            if (ship.getPosition().row == s.getPosition().row &&
                (col >= s.getPosition().col && col <= s.getPosition().col + s.getSize() - 1)) {
                overlaps = true;
                break;
            }
        }
        else {
            if (col == s.getPosition().col &&
                (ship.getPosition().row >= s.getPosition().row && ship.getPosition().row <= s.getPosition().row + s.getSize() - 1)) {
                overlaps = true;
                break;
            }
        }
    }
    return overlaps;
}

bool ShipBoard::ShipOverlapsAnotherShipRow(Ship& ship, const int& row) {
    bool overlaps{ false };
    for (Ship& s : ships) {
        if (&s == &ship) // If it's the same ship, skip it
            continue;
        if (s.getOrientation() == Ship_Orientation::SO_VERTICAL) {
            if (ship.getPosition().col == s.getPosition().col &&
                (row >= s.getPosition().row && row <= s.getPosition().row + s.getSize() - 1)) {
                overlaps = true;
                break;
            }
        }
        else {
            if (row == s.getPosition().row &&
                (ship.getPosition().col >= s.getPosition().col && ship.getPosition().col <= s.getPosition().col + s.getSize() - 1)) {
                overlaps = true;
                break;
            }
        }
    }
    return overlaps;
}

void ShipBoard::placeShipOnShipBoard(Ship& ship) {
    Cell_Type_Ship_Board ship_mark;
    switch (ship.getShipType()) {
    case Ship_Type::ST_AIRCRAFT_CARRIER:
        ship_mark = Cell_Type_Ship_Board::CT_AIRCRAFT_CARRIER;
        break;
    case Ship_Type::ST_BATTLESHIP:
        ship_mark = Cell_Type_Ship_Board::CT_BATTLESHIP;
        break;
    case Ship_Type::ST_CRUISER:
        ship_mark = Cell_Type_Ship_Board::CT_CRUISER;
        break;
    case Ship_Type::ST_DESTROYER:
        ship_mark = Cell_Type_Ship_Board::CT_DESTROYER;
        break;
    case Ship_Type::ST_SUBMARINE:
        ship_mark = Cell_Type_Ship_Board::CT_SUBMARINE;
        break;
    }
    ship_board.at(ship.getPosition().row - 1).at(ship.getPosition().col - 1) = ship_mark;
    if (ship.getOrientation() == Ship_Orientation::SO_HORIZONTAL) {
        for (int i{ ship.getPosition().col }; i < ship.getPosition().col - 1 + ship.getSize(); ++i) {
            ship_board.at(ship.getPosition().row - 1).at(i) = ship_mark;
        }
    }
    else {
        for (int i{ ship.getPosition().row }; i < ship.getPosition().row - 1 + ship.getSize(); ++i) {
            ship_board.at(i).at(ship.getPosition().col - 1) = ship_mark;
        }
    }
}

void ShipBoard::inisetShipBoard() {
    for (Ship& s : ships) {
        drawBoard();
        cout << endl;
        bool isValidPlacement{ false };
        do {
            s.iniShip();
            isValidPlacement = ShipBoard::isValidPlacement(s);
            if (!isValidPlacement) {
                cout << "The ship placement is invalid. Please do it better, dumbass!" << endl << endl;
            }
        } while (!isValidPlacement);
        placeShipOnShipBoard(s);
        iniUpdateBoard();
    }
    drawBoard();
    cout << endl;
}

void ShipBoard::iniUpdateBoard() {
    for (int i{ 0 }; i < Board::BOARD_SIZE; ++i) {
        for (int j{ 0 }; j < Board::BOARD_SIZE; ++j) {
            board.at(i).at(j) = cell_types.at(ship_board.at(i).at(j));
        }
    }
}

// GET METHODS
std::array<Ship, ShipBoard::NUM_SHIPS>& ShipBoard::getShips() { return ships; }
std::array<std::array<Cell_Type_Ship_Board, Board::BOARD_SIZE>, Board::BOARD_SIZE>& ShipBoard::getShipBoard() { return ship_board; }

// SET METHODS
void ShipBoard::setShipBoard(Position& pos, Cell_Type_Ship_Board type) {
    ship_board.at(pos.row - 1).at(pos.col - 1) = type; // - 1 because array is 0-indexed
    board.at(pos.row - 1).at(pos.col - 1) = cell_types.at(type); // Set board cell with corresponding std::string
}

void ShipBoard::setShips(Position& pos, Cell_Type_Ship_Board type) {
    Ship_Type ship_type{ Ship_Type::ST_AIRCRAFT_CARRIER }; // To initialize the variable
    switch (type) {
    case Cell_Type_Ship_Board::CT_AIRCRAFT_CARRIER:
        ship_type = Ship_Type::ST_AIRCRAFT_CARRIER;
        break;
    case Cell_Type_Ship_Board::CT_BATTLESHIP:
        ship_type = Ship_Type::ST_BATTLESHIP;
        break;
    case Cell_Type_Ship_Board::CT_CRUISER:
        ship_type = Ship_Type::ST_CRUISER;
        break;
    case Cell_Type_Ship_Board::CT_DESTROYER:
        ship_type = Ship_Type::ST_DESTROYER;
        break;
    case Cell_Type_Ship_Board::CT_SUBMARINE:
        ship_type = Ship_Type::ST_SUBMARINE;
        break;
    }
    for (auto& s : ships) {
        if (s.getShipType() == ship_type) {
            s.setHitPosition(pos);
        }
    }
}