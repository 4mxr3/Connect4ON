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
    for(int i = 0; i < gameBoard->row; i++)
    {
        count = 0;
        for(int j = 0; j < gameBoard->col; j++)
        {
            if(gameBoard->game[i][j] != turn)
                count = 0;
            else
                count++;
        }
        if(count == 4)
            return true;
    }
   
    //if no win reset count
    count = 0;
    
    //check column wins
    for(int i = 0; i < gameBoard->col; i++)
    {
        count = 0; 
        for(int j = 0; j < gameBoard->row; j++)
        {
            if(gameBoard->game[j][i] != turn)
                count = 0;
            else
                count++;
        }
        if(count == 4)
            return true;
    }
    
    //if no win reset count
    count = 0;
    
    //check diagonal up to down wins 
    for(int i = 0; i < gameBoard->row; i++)
    {
        for(int j = 0; j < gameBoard->col; j++){
            rows = i; 
            cols = j;
            if((count == 0 && i == 3) || (count == 0 && j == 4)){
                brk = true;
                break;
            }    
            if(gameBoard->game[rows][cols] == turn)
            {
                count = upDown(rows, cols, turn);
            }
            if(count == 4)
                return true;  
        }
        if(brk == true)
            break;
    }
    //check diagonal down to up wins
    for(int i = gameBoard->row - 1; i >= 0 ; i--)
    {
        for(int j = 0; j < gameBoard->col; j++){
            int rows = i; 
            int cols = j;
            if((count == 0 && i == 2) || (count == 0 && j == 4)){
                brk = true;
                break;
            }
            if(gameBoard->game[rows][cols] == turn)
            {
                count = downUp(rows, cols, turn);
            }
            if(count == 4)
                return true; 
        }
        if(brk == true)
            break; 
    }
    
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
    gameBoard = new BOARD; // Allocate memory for gameBoard itself
    gameBoard->row = 6;
    gameBoard->col = 7;
    gameBoard->game = new int*[gameBoard->row];
    for(int i = 0; i < gameBoard->row; i++){
        gameBoard->game[i] = new int[gameBoard->col];
        for(int j = 0; j < gameBoard->col; j++){
            gameBoard->game[i][j] = 0;
        }
    }
    player = 1;
    comp = 2;
    gOver = false;
}
