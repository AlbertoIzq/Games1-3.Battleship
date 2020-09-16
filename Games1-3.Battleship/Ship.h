#pragma once

#include <vector>

enum class Ship_Type
{
    ST_AIRCRAFT_CARRIER,
    ST_BATTLESHIP,
    ST_CRUISER,
    ST_DESTROYER,
    ST_SUBMARINE
};

struct Position {
    int row;
    int col;
};

enum class Ship_Orientation {
    SO_HORIZONTAL,
    SO_VERTICAL
};

class Ship {
private:
    static constexpr int AIRCRAFT_CARRIER_SIZE = 5;
    static constexpr int BATTLESHIP_SIZE = 4;
    static constexpr int CRUISER_SIZE = 3;
    static constexpr int DESTROYER_SIZE = 3;
    static constexpr int SUBMARINE_SIZE = 2;

    bool sunk_in_prev_turn;

    void iniPosition();
    void iniOrientation();
    void iniHitPositions();
protected:
    Ship_Type type;
    int size;
    Position position;
    Ship_Orientation orientation;
    std::vector<std::pair<Position, bool>> hit_positions;
    bool sunk_in_this_turn;
public:
    Ship(Ship_Type);
    void iniShip();
    bool isSunk();

    // GET METHODS
    Ship_Type getShipType() const;
    int getSize() const;
    Position getPosition() const;
    Ship_Orientation getOrientation() const;
    std::vector<std::pair<Position, bool>> getHitPositions() const;
    bool getSunkThisTurn();

    // SET METHODS
    void setHitPosition(Position&);
};