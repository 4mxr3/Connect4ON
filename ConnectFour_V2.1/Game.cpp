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

//Deconstructor
Game::~Game()
{
    for(int i = 0; i < gameBoard->row; i++)
        delete[] gameBoard->game[i];
    delete [] gameBoard->game;
}

//player move
int Game:: plaMove(int *spot)
{
    int column;
    display();
    bool verify = true;
    do{
        verify = true;
        cout << endl << "Please put a legal column(0 to 6, left to right)" << endl;
        cin>>column;
        if(column > 6 || column < 0){
            verify = false;
            cout<<"Please choose a different column";
        }
    }while(!verify);
        
    for(int i = 5; i>=0; i--){
        if(gameBoard->game[i][column] == 0){
            gameBoard->game[i][column] = player;
            break;
        }
    }
    cout<<"Player Turn"<<endl;
    display();
    cout<<endl;
    spot++;
    return player;
}

int Game::AIMove(int *spot)
{
    int move = rand()%6;
    for(int i = 5; i>=0; i--){
        if(gameBoard->game[i][move] == 0){
            gameBoard->game[i][move] = comp;
            break;
        }
    }
    cout<<"Computer Turn"<<endl;
    spot++;
    return comp;
}

bool Game::win(int turn)
{
    /*
     * win conditions
     * 1. if 0, then reset whole thing
     * 2. if 0 and player = 0, then mark first spot
     * 3. if spot = player, then tally win condtion
     * 4. else not, then switch over to other player filling spot
     */
    //declare and initialize variables
    bool brk = false;
    int count = 0; 
    int rows, cols = 0;
    
    //check row wins
    for (int i = 0; i < gameBoard->row; i++)
    {
        int count = 0;
        for (int j = 0; j < gameBoard->col; j++)
        {
            if (gameBoard->game[i][j] == turn)
            {
                count++;
                if (count == 4)
                    return true;
            }
            else
            {
                count = 0; // Reset count if not consecutive
            }
        }
    }

   
    //if no win reset count
    count = 0;
    
    //check column wins
    for (int j = 0; j < gameBoard->col; j++)
    {
        int count = 0;
        for (int i = 0; i < gameBoard->row; i++)
        {
            if (gameBoard->game[i][j] == turn)
            {
                count++;
                if (count == 4)
                    return true;
            }
            else
            {
                count = 0; // Reset count if not consecutive
            }
        }
    }
    
    //if no win reset count
    count = 0;
    
    //for checking diagonal win conditions
    for (int i = 0; i < gameBoard->row - 3; i++)
    {
        for (int j = 0; j < gameBoard->col - 3; j++)
        {
            //diagonals from top-left to bottom-right
            if (gameBoard->game[i][j] == turn &&
                gameBoard->game[i + 1][j + 1] == turn &&
                gameBoard->game[i + 2][j + 2] == turn &&
                gameBoard->game[i + 3][j + 3] == turn)
            {
                return true;
            }

            // diagonals from top-right to bottom-left
            if (gameBoard->game[i][j + 3] == turn &&
                gameBoard->game[i + 1][j + 2] == turn &&
                gameBoard->game[i + 2][j + 1] == turn &&
                gameBoard->game[i + 3][j] == turn)
            {
                return true;
            }
        }
    }

    return false;
    
    //if no wins at all 
    return false;
}

int Game::upDown(int row, int col, int turn){
    int count = 1;
    for(int i = 1; i < 4; i++){
        if(gameBoard->game[row + i][col + i] == turn)
        {
            count++;
        }
        else count = 0;
    }
    return count;
}

int Game::downUp(int row, int col, int turn){
    int count = 1;
    for(int i = 1; i < 4; i++){
        if(gameBoard->game[row - i][col + i] == turn)
        {
            count++;
        }
        else count = 0;
    }
    return count;
}

void Game::display(){
    for (int i = 0; i < gameBoard->row; i++)
    {
        for (int j = 0; j < gameBoard->col; j++)
        {cout << gameBoard->game[i][j] << " ";}
        cout << endl;
    }
    
}

//Constructor
Game::Game(){
    //initialize variables
    //game board
    gameBoard->row = 6;
    gameBoard->col = 7;
    gameBoard->game = new int*[gameBoard->row];
    for(int i = 0; i < gameBoard-> col; i++){
        gameBoard->game[i]=new int[gameBoard->col];
    }
    
    for(int i = 0; i < gameBoard->row; i++)
    {
        for(int j = 0; j < gameBoard->col; j++){
            gameBoard->game[i][j] = 0;
        }
    }
    
    //players
    player = 1;
    comp = 2;
    
    //game
    gOver = false;
}
