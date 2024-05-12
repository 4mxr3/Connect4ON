/*
 * File:   game.cpp
 * Author: Janaye Jackson
 * 
 * Created on April 8th, 2024, 11:11 a.m.
 * 
 * Purpose: To implement a connect 4 game with 
 *          a cpu.
 */

#include <iostream>   //I/O Library
#include <cstdlib>    //Random Number Generator, Setting seed, etc....
#include <iomanip>    //Formatting Library
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

//User Defined Libraries
#include "Game.h"

//Deconstructor

Game::~Game() {
    for (int i = 0; i < gameBoard->row; i++)
        delete[] gameBoard->game[i];
    delete [] gameBoard->game;
}

//player move

int Game::plaMove(int *spot, int playerNumber) {
    bool verify = false;
    do {
        cout << endl << "Player " << playerNumber << ", please put a legal column (0 to 6, left to right): ";
        cin >> pMove;

        // Adjust the player input here to align with 0-based array indexing
        pMove--;  // Subtract 1 from the input to match the 0-based index of the array

        // Check if the input is not an integer, out of range, or not in the valid range
        if (cin.fail() || pMove > 6 || pMove < 0) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore wrong input
            cout << "Invalid input. Please choose a valid column." << endl;
        } else {
            // Check if the column is full
            if (gameBoard->game[0][pMove] != 0) {
                cout << "Column " << pMove + 1 << " is full. Please choose a different column." << endl;
            } else {
                verify = true; // Input is valid and column is not full
            }
        }
    } while (!verify);

    // Place the marker in the lowest empty spot in the column
    for (int i = 5; i >= 0; i--) {
        if (gameBoard->game[i][pMove] == 0) {
            gameBoard->game[i][pMove] = playerNumber;
            break;
        }
    }

    // Inform player of their turn and display board state
    cout << "Player " << playerNumber << "'s Turn" << endl;
    display();   
    cout << endl;
    spot++;
    return playerNumber;
}

int Game::AIMove(int *spot) {
    int move = rand() % 7; // Change to ensure AI considers all columns equally
    bool success = false;

    while (!success) {
        for (int i = 5; i >= 0; i--) {
            // Check if current slot is empty
            if (gameBoard->game[i][move] == 0) {
                // Additional check to ensure the token is placed in the lowest possible spot
                if (i == 5 || gameBoard->game[i + 1][move] != 0) {
                    gameBoard->game[i][move] = comp;
                    success = true;
                    break;
                }
            }
        }

        // If a valid move hasn't been made, choose another column
        if (!success) {
            move = (move + 1) % 7; // Cycle through columns
        }
    }

    cout << "Computer Turn" << endl;
    display();
    spot++;
    return comp;
}

bool Game::win(int turn) {
    /*
     * win conditions
     * 1. if 0, then reset whole thing
     * 2. if 0 and player = 0, then mark first spot
     * 3. if spot = player, then tally win condtion
     * 4. else not, then switch over to other player filling spot
     */
    //declare and initialize variables
    int count = 0;

    //check row wins
    for (int i = 0; i < gameBoard->row; i++) {
        int count = 0;
        for (int j = 0; j < gameBoard->col; j++) {
            if (gameBoard->game[i][j] == turn) {
                count++;
                if (count == 4)
                    return true;
            } else {
                count = 0; // Reset count if not consecutive
            }
        }
    }


    //if no win reset count
    count = 0;

    //check column wins
    for (int j = 0; j < gameBoard->col; j++) {
        int count = 0;
        for (int i = 0; i < gameBoard->row; i++) {
            if (gameBoard->game[i][j] == turn) {
                count++;
                if (count == 4)
                    return true;
            } else {
                count = 0; // Reset count if not consecutive
            }
        }
    }

    //if no win reset count
    count = 0;

    //for checking diagonal win conditions
    for (int i = 0; i < gameBoard->row - 3; i++) {
        for (int j = 0; j < gameBoard->col - 3; j++) {
            //diagonals from top-left to bottom-right
            if (gameBoard->game[i][j] == turn &&
                    gameBoard->game[i + 1][j + 1] == turn &&
                    gameBoard->game[i + 2][j + 2] == turn &&
                    gameBoard->game[i + 3][j + 3] == turn) {
                return true;
            }

            // diagonals from top-right to bottom-left
            if (gameBoard->game[i][j + 3] == turn &&
                    gameBoard->game[i + 1][j + 2] == turn &&
                    gameBoard->game[i + 2][j + 1] == turn &&
                    gameBoard->game[i + 3][j] == turn) {
                return true;
            }
        }
    }

    return false;

    //if no wins at all 
    return false;
}

void Game::display() {
    for (int i = 0; i < gameBoard->row; i++) {
        for (int j = 0; j < gameBoard->col; j++) {
            cout << gameBoard->game[i][j] << " ";
        }
        cout << endl;
    }
}

void Game::playerVsPlayer() {
    int *spots = 0;
    int turn;
    bool gOver;
    int moves = 42;

    do {
        // Player 1's move
        turn = plaMove(spots, 1);
        gOver = win(turn);
        if (gOver)
            break;

        // Check if game is over after Player 1's move
        if (spots >= &moves || gOver)
            break;

        // Player 2's move
        turn = plaMove(spots, 2);
        gOver = win(turn);
    } while (spots < &moves && !gOver);


    if (spots == &moves && !gOver) {
        cout << "The game ended in a tie" << endl;
        data.updateRecord(gameBoard->game, 3);
        reset();
    }
    if (gOver && turn == 1) {
        cout << "Player 1 is the winner" << endl;
        data.updateRecord(gameBoard->game, 1);
        reset();
    } else if (gOver && turn == 2) {
        cout << "Player 2 is the winner" << endl;
        data.updateRecord(gameBoard->game, 2);
        reset();
    }
}

void Game::playerVsComputer() {
    int player = 1; // Player 1 starts the game
    int spots = 0; // Initialize spots to 0
    int turn;
    bool gOver;
    int moves = 42;

    do {
        // Player's move
        turn = plaMove(&spots, player);
        gOver = win(turn);
        if (gOver)
            break;

        // Check if game is over after player's move
        if (spots >= moves || gOver)
            break;

        // Computer's move
        turn = AIMove(&spots);
        gOver = win(turn);
    } while (spots < moves && !gOver);

    if (spots >= moves && !gOver) {
        cout << "The game ended in a tie" << endl;
        data.updateRecord(gameBoard->game, 3);
        reset();
    }
    if (gOver && turn == 1) {
        cout << "You are the winner" << endl;
        data.updateRecord(gameBoard->game, 1);
        reset();
    } else {
        cout << "The computer won" << endl;
        data.updateRecord(gameBoard->game, 2);
        reset();
    }
}

//Constructor

Game::Game(BinaryInterface bin) {
    //initialize variables
    //game board
    gameBoard = new BOARD;
    gameBoard->row = 6;
    gameBoard->col = 7;
    gameBoard->game = new int*[gameBoard->row];
    for (int i = 0; i < gameBoard-> col; i++) {
        gameBoard->game[i] = new int[gameBoard->col];
    }

    for (int i = 0; i < gameBoard->row; i++) {
        for (int j = 0; j < gameBoard->col; j++) {
            gameBoard->game[i][j] = 0;
        }
    }

    //players
    player = 1;
    comp = 2;

    //game
    gOver = false;

    //Copy over user login
    data = bin;
    
    menu();
}

void Game::printStats() {
    data.printStats();
}

void Game::reset() {
    gameBoard = new BOARD;
    gameBoard->row = 6;
    gameBoard->col = 7;
    gameBoard->game = new int*[gameBoard->row];
    for (int i = 0; i < gameBoard-> col; i++) {
        gameBoard->game[i] = new int[gameBoard->col];
    }

    for (int i = 0; i < gameBoard->row; i++) {
        for (int j = 0; j < gameBoard->col; j++) {
            gameBoard->game[i][j] = 0;
        }
    }
}

void Game::menu() {
    int choice;
    do {

        cout << "Menu:" << endl;
        cout << "1. Player vs player" << endl;
        cout << "2. Player vs computer" << endl;
        cout << "3. Print Stats" << endl;
        cout << "4. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                playerVsPlayer();
                break;
            case 2:
            {
                playerVsComputer();
                break;
            }
            case 3:
                printStats();
                break;
            case 4:
                cout << "Exiting the game. Goodbye!" << endl;
                return;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    } while (choice != 4);
}