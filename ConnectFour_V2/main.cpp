/*
 * File:   main.cpp
 * Author: Janaye Jackson
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
    
    //Declare & Initialize Variables
    Game game1;
    int *spots = 0;
    int turn;
    bool gOver;
    int moves = 42;
    do{
       turn = game1.plaMove(spots);
       gOver = game1.win(turn);
       if(gOver)
           break;
       turn = game1.AIMove(spots);
       gOver = game1.win(turn);
    }while(spots < &moves && !gOver);
    
    //tie game
    if(spots == &moves && !gOver){
        cout<<"The game ended in a tie"<<endl;
    }
    if(gOver && turn == 1)
    {
        cout<<"You are the winner";
    }
    else
    {
        cout<<"The computer won";
    }
    //Exit the program

    return 0;
}

