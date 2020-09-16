#include "UtilsLib.h"
#include "Ship.h"
#include "Board.h"

#include <iostream>

using namespace InputValidation;

using std::cin;
using std::cout;
using std::endl;

Ship::Ship(Ship_Type type)
	: type{ type } {
	switch (type) {
	case Ship_Type::ST_AIRCRAFT_CARRIER:
		size = AIRCRAFT_CARRIER_SIZE;
		break;
	case Ship_Type::ST_BATTLESHIP:
		size = BATTLESHIP_SIZE;
		break;
	case Ship_Type::ST_CRUISER:
		size = CRUISER_SIZE;
		break;
	case Ship_Type::ST_DESTROYER:
		size = DESTROYER_SIZE;
		break;
	case Ship_Type::ST_SUBMARINE:
		size = SUBMARINE_SIZE;
		break;
	}
	sunk_in_prev_turn = false;
	sunk_in_this_turn = false;
}

void Ship::iniShip() {
	iniPosition();
	iniOrientation();
	iniHitPositions();
}

void Ship::iniPosition() {
	cout << "-Set a starting position for a " << size << " length ship:" << endl;
	cout << "Row (1 - " << Board::BOARD_SIZE << "): ";
	position.row = inputValidatorSpecific<int>(1, Board::BOARD_SIZE);
	cout << "Col (1 - " << Board::BOARD_SIZE << "): ";
	position.col = inputValidatorSpecific<int>(1, Board::BOARD_SIZE);
	cout << endl;
}

void Ship::iniOrientation() {
	cout << "-Set a orientation, horizontal/vertical (h/v): ";
	char orient = inputValidatorSpecificValueAndLength<char>(std::vector<char>{'H', 'V', 'h', 'v'}, 1);
	if (orient == 'H' || orient == 'h')
		orientation = Ship_Orientation::SO_HORIZONTAL;
	else if (orient == 'V' || orient == 'v')
		orientation = Ship_Orientation::SO_VERTICAL;
	cout << endl;
}

void Ship::iniHitPositions() {
	for (int i{ 0 }; i < size; ++i) {
		if (orientation == Ship_Orientation::SO_HORIZONTAL) {
			hit_positions.push_back(std::make_pair(Position{ position.row, position.col + i }, bool{ false }));
		}
		else {
			hit_positions.push_back(std::make_pair(Position{ position.row + i, position.col }, bool{ false }));
		}
	}
}

bool Ship::isSunk() {
	bool is_sunk = true;
	for (auto e : hit_positions) {
		if (e.second == false) {
			is_sunk = false;
			break;
		}
	}
	return is_sunk;
}

// GET METHODS
Ship_Type Ship::getShipType() const { return type; }
int Ship::getSize() const { return size; }
Position Ship::getPosition() const { return position; }
Ship_Orientation Ship::getOrientation() const { return orientation; }
std::vector<std::pair<Position, bool>> Ship::getHitPositions() const { return hit_positions; }
bool Ship::getSunkThisTurn() {
	if (sunk_in_this_turn) {
		sunk_in_prev_turn = true;
		sunk_in_this_turn = false;
	}
	if (isSunk() && !sunk_in_prev_turn) {
		sunk_in_this_turn = true;
	}
	return sunk_in_this_turn;
}

// SET METHODS
void Ship::setHitPosition(Position& pos) {
	for (auto& p : hit_positions) {
		if (p.first.row == pos.row && p.first.col == pos.col) {
			p.second = true;
		}
	}
}