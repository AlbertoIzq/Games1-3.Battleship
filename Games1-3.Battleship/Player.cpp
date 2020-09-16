#include "UtilsLib.h"
#include "Player.h"

#include <iostream>

using namespace InputValidation;

Player::Player() {
	std::cout << "-Write a name for the player: ";
	name = inputValidator<std::string>();
	std::cout << std::endl;
	ship_board.inisetShipBoard();
}

Player& Player::operator=(const Player& other_player) {
	name = other_player.name;
	guess_board = other_player.guess_board;
	ship_board = other_player.ship_board;
	return *this;
}

// GET METHODS
std::string Player::getName() const { return name; }
GuessBoard& Player::getGuessBoard() { return guess_board; }
ShipBoard& Player::getShipBoard() { return ship_board; }

void Player::updateGuessBoard(Position& pos, Player& other_player) {
	Cell_Type_Ship_Board cell = other_player.getShipBoard().getShipBoard().at(pos.row - 1).at(pos.col - 1);
	if (cell == Cell_Type_Ship_Board::CT_AIRCRAFT_CARRIER || cell == Cell_Type_Ship_Board::CT_BATTLESHIP
		|| cell == Cell_Type_Ship_Board::CT_CRUISER || cell == Cell_Type_Ship_Board::CT_DESTROYER || cell == Cell_Type_Ship_Board::CT_SUBMARINE) {
		getGuessBoard().setGuessBoard(pos, Cell_Type_Guess_Board::CT_HIT);
	}
	else {
		getGuessBoard().setGuessBoard(pos, Cell_Type_Guess_Board::CT_MISSED);
	}
}

void Player::updateShipBoard(Position& pos) {
	Cell_Type_Ship_Board cell = getShipBoard().getShipBoard().at(pos.row - 1).at(pos.col - 1);
	switch (cell) {
	case Cell_Type_Ship_Board::CT_AIRCRAFT_CARRIER:
		getShipBoard().setShipBoard(pos, Cell_Type_Ship_Board::CT_AIRCRAFT_CARRIER_HIT);
		break;
	case Cell_Type_Ship_Board::CT_BATTLESHIP:
		getShipBoard().setShipBoard(pos, Cell_Type_Ship_Board::CT_BATTLESHIP_HIT);
		break;
	case Cell_Type_Ship_Board::CT_CRUISER:
		getShipBoard().setShipBoard(pos, Cell_Type_Ship_Board::CT_CRUISER_HIT);
		break;
	case Cell_Type_Ship_Board::CT_DESTROYER:
		getShipBoard().setShipBoard(pos, Cell_Type_Ship_Board::CT_DESTROYER_HIT);
		break;
	case Cell_Type_Ship_Board::CT_SUBMARINE:
		getShipBoard().setShipBoard(pos, Cell_Type_Ship_Board::CT_SUBMARINE_HIT);
		break;
	case Cell_Type_Ship_Board::CT_NONE:
		getShipBoard().setShipBoard(pos, Cell_Type_Ship_Board::CT_MISSED);
		break;
	}
	getShipBoard().setShips(pos, cell);
}

void Player::drawShipBoard() {
	cout << "- Ship Board:" << endl << endl;
	getShipBoard().drawBoard();
	cout << endl;
}

void Player::drawGuessBoard() {
	cout << "- Guess Board:" << endl << endl;
	getGuessBoard().drawBoard();
	cout << endl;
}

void Player::aShipHasBeenSunk() {
	for (auto& s : getShipBoard().getShips()) {
		if (s.getSunkThisTurn()) {
			cout << "You have sunk a ship of " << getName() << ". A ship of size " << s.getSize() << ". One less to beat your stupid rival!" << endl << endl;
		}
	}
}

bool Player::allShipsAreSunk() {
	bool all_ship_sunk{ true };
	for (auto& s : getShipBoard().getShips()) {
		if (!s.isSunk()) {
			all_ship_sunk = false;
			break;
		}
	}
	return all_ship_sunk;
}