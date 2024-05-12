
/* 
 * File:   Game.h
 * Author: Janaye Jackson
 *
 * Created on March 22, 2024, 11:44 AM
 */

#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "BinaryInterface.h"

class Game {
private:
    BOARD *gameBoard;
    BinaryInterface data;
    bool gOver;
    int player, comp, pMove;

    // Helper function for AI to use minimax algorithm
    int minimax(BOARD*, int depth, bool isMaximizingPlayer, int alpha, int beta);
    
    // Evaluates the current board position
    int evaluatePosition(BOARD*);

public:
    Game(BinaryInterface); // Constructor
    ~Game(); // Destructor
    void display(); // Display the game board
    int plaMove(int*, int); // Handle player moves
    int AIMove(int*); // Handle AI moves using enhanced logic
    int upDown(int, int, int);
    int downUp(int, int, int);
    bool win(int); // Check if a player has won
    void playerVsPlayer();
    void playerVsComputer();
    
    void printStats(); // Helper function to print binary data
    void menu();
    void reset(); // Reset the game to initial state
};

#endif /* GAME_H */


