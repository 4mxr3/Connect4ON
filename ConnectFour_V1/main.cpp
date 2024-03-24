/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: patri
 *
 * Created on March 10, 2024, 10:56 PM
 */

#include <cstdlib>
#include <iostream>
using namespace std;

struct BOARD
{
    const int row = 6;
    const int col = 7;
    int game[6][7 ]; // a standard connect four game is 6 x 7
    int spotsCovered = 0; // when it hits 42, game is automatically over
};
void display(BOARD);
bool winMaybe(BOARD);
int main(int argc, char** argv)
{
    BOARD Game1;
    for (int i = 0; i < Game1.row; i++)
    {
        for (int j = 0; j < Game1.col; j++)
        {Game1.game[i][j] = 0;}
    }
    
    // now let's get the players settled
    bool lost = false;
    int player1 = 1; // 1 is 1st player
    int player2 = 2; // 2 is 2nd player
    int currentTurn = 1; // if 1, convert 2, if 2, convert 1 to swap turns
    while (Game1.spotsCovered < 42 || lost)
    {
        int column; // playing piece
        display (Game1);
        bool illegalPlay = false;
        do
        {
            illegalPlay = false;
            cout << endl << "Player " << currentTurn << " please put at a legal column(0 to 6, left to right)" << endl;
            
            cin >> column;
            // CHECK IF COLUMN IS EMPTY
            if (Game1.game[0][column] != 0) // We shall check the top
            {illegalPlay = true;cout << "Please choose a different number" << endl;} 
        }while(illegalPlay == true);
        
        // PUT PIECE In
        for (int i = 5; i >= 0; i--) // start top to bottom
        {
            if (Game1.game[i][column] == 0)
            {Game1.game[i][column] = currentTurn; i = -1;} // FORCE EXIT by making i > rows
        }
        
        // CHECK WIN CONDTIONS
        
        // at the very end, switch tunrs
        if (currentTurn == 1)
        {currentTurn = 2;}
        else
        {currentTurn = 1;}
    }
    
    // DISPLAY WINNERS -> TIE ONLY OCCURS IF spots =42 and no win has been confirnmed
    return 0;
}

void display(BOARD g)
{
    for (int i = 0; i < g.row; i++)
    {
        for (int j = 0; j < g.col; j++)
        {cout << g.game[i][j] << " ";}
        cout << endl;
    }
}
// ROW 5 is the BOTTOM ROW
bool winMaybe(BOARD g)
{
    /*
             win conditions
             * 1. if 0, then reset whole thing
             * 2. if 0 and player = 0, then mark first spot
             * 3. if spot = player, then tally win condtion
             * 4. else not, then switch over to other player filling spot
             */
    // ROWS
    int count = 0; // if count is 5, then its a win
    int player = 0;
    for (int i = 0; i < g.row; i++)
    {
        count = 0; player = 0;// new row
        for (int j = 0; j < g.col; j++)
        {
            if (g.game[i][j] == 0) // 0 resets counter
            {count = 0; player = 0;} 
            else if (g.game[i][j] != 0 && player == 0) // non-zero first move sets players
            {count++; player = g.game[i][j];}
            else if (g.game[i][j] == player) // increment
            {count++;}
            else
            {
                count = 0; player = g.game[i][j];
            }
            if (count ==4) // keep checking wins
            {return true;}
        }
    }
    count = 0; player = 0;// reset if out here
    
    // COLUMNS => SAME LOGIC JUST FLIP UPside donw
    for (int i = 0; i < g.col; i++)
    {
        count = 0; player = 0; // new column
        for (int j = 0; j < g.row; j++)
        {
            if (g.game[j][i] == 0) // 0 resets counter
            {count = 0; player = 0;} 
            else if (g.game[j][i] != 0 && player == 0) // non-zero first move sets players
            {count++; player = g.game[j][i];}
            else if (g.game[j][i] == player) // increment
            {count++;}
            else
            {
                count = 0; player = g.game[j][i];
            }
            if (count ==4) // keep checking wins
            {return true;}
        }
    }
    count = 0; player = 0; // next test 
}