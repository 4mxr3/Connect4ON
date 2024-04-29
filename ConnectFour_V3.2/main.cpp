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
    srand(static_cast<unsigned int> (time(0)));

    BinaryInterface bin;

    int result = bin.login();

    switch (result) {
        case 1:
            //ADMIN LOGIN
            bin.adminMenu();
            break;
        case 0: {
            //USER LOGIN
            Game game1(bin);
            break;
        }
        default:
            cout << "Error logging in. Exiting program." << endl;
            return 0;
    };

    return 0;
}

