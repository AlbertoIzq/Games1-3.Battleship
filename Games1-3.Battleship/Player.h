#pragma once

#include "GuessBoard.h"
#include "ShipBoard.h"
#include "Ship.h"

#include <string>

class Player {
private:
    //static constexpr const char* DEF_NAME = "Player";
    const std::string DEF_NAME = "Player";

protected:
    std::string name;
    GuessBoard guess_board;
    ShipBoard ship_board;
public:
    Player();
    Player& operator=(const Player&);

    // GET METHODS
    std::string getName() const;
    GuessBoard& getGuessBoard();
    ShipBoard& getShipBoard();

    void updateGuessBoard(Position&, Player&); // ????
    void updateShipBoard(Position&); // ????
    void drawShipBoard();
    void drawGuessBoard();
    void aShipHasBeenSunk();
    bool allShipsAreSunk();

};
