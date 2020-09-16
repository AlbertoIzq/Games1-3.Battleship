// Description and draft code
/*
_____DESCRIPTION_____

The game is played on four 10x10 grids by 2 players, with each player having 2 grids each.
 The rows of the grid go from A to J in the rows and 1 to 10 in the columns. Each player will arrange their ships on
 their respective ship board before the main game starts. Each ship occupies a number of consecutive squares on the
 grid, arranged either horizontally or vertically. The number of squares for each ship is determined by the type
 of the ship. The ships cannot overlap.

 The ships are as follows:

 Ship type       		Size
 --------------------+----------
 Aircraft carrier    |    5
 Battleship          |    4
 Cruiser             |    3
 Destroyer           |    3
 Submarine           |    2

 After the ships have been positioned, the game proceeds in a series of rounds. In each round, each player takes a turn
 to announce a target square in the opponent's grid which is to be shot at. The opponent announces whether or not
 the square is occupied by a ship, and if it is a miss, the player marks their guess board as a miss; if it is a hit
 they mark it as a hit. This is to build up a picture of the opponent's fleet. If the guess was a hit, the attacked
 player will mark their ship as hit in the guessed location. That will end the turn.

 When all of the squares of a ship have been hit, the ship is sunk and there is output about what ship was sunk.
 If all the player's ship have been sunk, the game is over and their opponent wins.


+---+
|   |
+---+

        +---------------+
Input   |               |
--------+               |   Output
        |     XForm     +---------
--------+               |
        |               |
        +---------------+


    General:
    - Ships
    - Boards
    - Players
    - Guess (position on the board)

    Ships
    -----
    -5 types - listed above
    -Have a size
    -Has a position on the board (row between A - J, columns between 1 - 10)
    -Orientation (either vertical or horizontal)
    -Can be damaged in a specific spot

    Boards
    ------
    - 2 different boards - Ship boards (where you place all your ships), guess board (your view of the opponent's board)
    - Each position on the Guess board can be in 3 states - hit, miss, we haven't guessed the spot
    - Board for ships - contain all the player's ships at certain locations, we place markers on the spots where our
            ships have been hit

    Players
    -------
    - Name
    - All the ships
    - Guess board
    - Ship board

    Guess
    -----
    - Position on the board
    - Position has a row (A - J), columns (1 - 10)

_____HOW TO SOLVE IT?_____

___Step 1

initPlayer(player1, "Player1");
initPlayer(player2, "Player2");
do {
    playGame(player1, player2);
} while (wantToPlayAgain());

___Step 2

-playGame:

setupBoard(player1);
setupBoard(player2);
do {
    drawBoards(current_player);
    do {
        Prompt the current player for a guess
        guess = getGuess()
    } while (!isGuessValid(guess, current_player));
    updateBoards(guess, current_player, other_player);
    drawBoard(current_player); // to see the result of the guess
    if (a ship is sunk on current player's turn) {
        output that the current player sunk that ship
    }
    waitForKeyPress();
    switchPlayers();

} while (!gameIsOver());
displayWinner();

-setupBoard(player)

clearBoards(player)

for (all the ships) {
    drawBoards(player)
    current_ship = get the current ship
    do {
        position = Get board position for the head of the ship
        orientation = Get the ship orientation
        isValidPlacement = isValidPlacement(current_ship, position, orientation)
        if (!isValidPlacement) {
            output to the player that it was not a valid placement
        }
    } while (!isValidPlacement);
    placeShipOnBoard(player, current_ship, position, orientation)

-isValidPlacement(current_ship, position, orientation)

if (orientation == HORIZONTAL) {
    for (all the columns the current_ship would take up) {
        if (ship will overlap another ship or the ship will be the off horizontally) {
            return false
        }
    }
} else {
    for (all the rows the current_ship would take up) {
        if (ship will overlap another ship or the ship will be the off vertically) {
            return false
        }
    }
}
return true

-placeShipOnBoard(player, current_ship, position, orientation)

ship.position = position
ship.orientation = orientation

if (orientation == HORIZONTAL) {
    for (all the columns the ship would take up) {
        set the ship part on the board at position.row an current column
    }
} else {
    for (all the rows the ship would take up) {
        set the ship part on the board at position.col an current row
    }
}

-updateBoards(guess, current_player, other_player)

if (other_player's ship board at guess is a ship) {
    // hit
    set hit on the current_player's guess board
    apply damage to the other_player's ship_board
} else {
    set miss on the current_player's guess board
    return ST_NONE
}

-isGameOver(player1, player2)

return areAllShipsSunk(player1) || areAllShipsSunk(player2)

-areAllShipsSunk(player)

for (all the player's ships) {
    if (!isSunk(player, currentShip)) {
        return false
    }
}
return true

-isSunk(player, ship)

if(ship.orientation == HORIZONTAL) {
    for (columns that ship takes up) {
        if (current_position on the shipBoard is not hit) {
            return false
        }
    }
} else {
    for (rows that ship takes up) {
        if (current_position on the shipBoard is not hit) {
            return false
        }
    }
}
return true

_____FUNCTIONS_____

*/

#include "UtilsLib.h"
#include "Player.h"
#include "ShipBoard.h"
#include "GuessBoard.h"
#include "Ship.h"

#include <iostream>
#include <vector>
#include <array>

using std::cin;
using std::cout;
using std::endl;

using namespace InputValidation;
using namespace Other;

void displayGameHeader();
void displayGameAbbreviations();
void playGame(Player&, Player&);
Position getGuess();
bool isGuessValid(Position&, Player&);
void switchPlayers(Player&, Player&);
bool gameIsOver(Player&, Player&);
void displayWinner(Player&, Player&);
bool wantToPlayAgain();

int main()
{
    displayGameHeader();
    displayGameAbbreviations();
    do {
        cout << "___SETTING PLAYER 1___" << endl << endl;
        Player player1;
        clearScreen();
        cout << "___SETTING PLAYER 2___" << endl << endl;
        Player player2;
        clearScreen();
        playGame(player1, player2);
    } while (wantToPlayAgain());

    return 0;
}

void displayGameHeader() {
    const std::string headline{ "Release date: XX/03/2020\nAuthor: Albertroll\nCopyright-All rights reserved" };
    cout << headline << endl << endl;
    cout << "Welcome to this stupid Battleship game!" << endl << endl;
}

void displayGameAbbreviations() {
    const std::array<std::string, 8> ABBREVIATIONS_BOARD{
        "None:   ",
        "Missed: X ",
        "Hit:* *",
        "Ship-Aircraft carrier: A ",
        "Ship-Battleship: B ",
        "Ship-Cruiser: C ",
        "Ship-Destroyer: D ",
        "Ship-Submarine: S ",
    };

    cout << "___LIST OF ABBREVIATIONS___" << endl << endl;
    for (int i{ 0 }; i < static_cast<int>(ABBREVIATIONS_BOARD.size()); ++i) {
        cout << ABBREVIATIONS_BOARD.at(i) << endl;
    }
    cout << endl;
}

void playGame(Player& player1, Player& player2) {
    Player current_player{ player1 };
    Player other_player{ player2 };
    do {
        cout << "___" << current_player.getName() << "'s TURN___" << endl << endl;
        current_player.drawShipBoard();
        current_player.drawGuessBoard();
        Position guess{ 0,0 };
        do {
            guess = getGuess();
        } while (!isGuessValid(guess, current_player));
        current_player.updateGuessBoard(guess, other_player);
        other_player.updateShipBoard(guess);
        current_player.drawGuessBoard();
        other_player.aShipHasBeenSunk();
        system("pause"); // Wait for key press
        clearScreen();
        switchPlayers(current_player, other_player);
    } while (!gameIsOver(current_player, other_player));
    displayWinner(current_player, other_player);
}

Position getGuess() {
    Position guess{ 0, 0 };
    cout << "-What's your shitty guess?" << endl;
    cout << "Row (1 - " << Board::BOARD_SIZE << "): ";
    guess.row = inputValidatorSpecific<int>(1, Board::BOARD_SIZE);
    cout << "Col (1 - " << Board::BOARD_SIZE << "): ";
    guess.col = inputValidatorSpecific<int>(1, Board::BOARD_SIZE);
    cout << endl;
    return guess;
}

bool isGuessValid(Position& guess, Player& player) {
    bool guess_valid{ true };
    if (guess.row < 1 || guess.row > Board::BOARD_SIZE || guess.col < 1 || guess.col > Board::BOARD_SIZE) { // If it's a value within the board
        guess_valid = false;
        cout << "Invalid guess. Position must be within the board limits!" << endl;
    }
    else if (player.getGuessBoard().getGuessBoard().at(guess.row - 1).at(guess.col - 1) != Cell_Type_Guess_Board::CT_NONE) { // If it's not been guessed before
        guess_valid = false;
        cout << "Invalid guess. You have already tried to guess this position, you stupid!" << endl;
        cout << endl;
    }
    return guess_valid;
}

void switchPlayers(Player& player1, Player& player2) {
    Player temp = player1;
    player1 = player2;
    player2 = temp;
}

bool gameIsOver(Player& player1, Player& player2) {
    return player1.allShipsAreSunk() || player2.allShipsAreSunk();
}

void displayWinner(Player& player1, Player& player2) {
    cout << "And the winner is...";
    if (player1.allShipsAreSunk()) {
        cout << player2.getName() << "! Congratulations, well played." << endl
            << player1.getName() << ", go cry to a corner. Loooooser!" << endl;
    }
    else if (player2.allShipsAreSunk()) {
        cout << player1.getName() << "! Congratulations, well played." << endl
            << player2.getName() << ", go cry to a corner. Loooooser!" << endl;
    }
    else {
        cout << "The game has ended in a draw. There are no winners or losers, oh damn!" << endl;
    }
    cout << endl;
}

bool wantToPlayAgain() {
    cout << "Do you feel like playing again this mind-blowing game? (y/n): ";
    char user_answer = inputValidatorSpecificValueAndLength<char>(std::vector<char>{'Y', 'N', 'y', 'n'}, 1);
    user_answer = tolower(user_answer);
    bool play_again{ false };
    if (user_answer == 'y') {
        play_again = true;
        cout << endl;
    }
    return play_again;
}