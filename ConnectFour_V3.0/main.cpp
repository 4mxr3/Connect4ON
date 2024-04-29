/*
 * File:   main.cpp
 * Author: Online Connect 4 Group
 * 
 * Created on March 22nd, 2024, 11:40 a.m.
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

//Global Constants, not Global Variables
//These are recognized constants from the sciences
//Physics/Chemistry/Engineering and Conversions between
//systems of units

//Function Prototypes

//Execution begins here!
int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));
    
    Game game1;
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
                game1.playerVsPlayer();
                break;
            case 2: {
                game1.playerVsComputer(); 
                break;
            }
            case 3:
                game1.printStats();
                break;
            case 4:
                cout << "Exiting the game. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    } while (choice != 4);

    return 0;
}
 
