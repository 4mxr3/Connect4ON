
/* 
 * File:   Game.h
 * Author: Janaye Jackson
 *
 * Created on March 22, 2024, 11:44 AM
 */

#ifndef GAME_H
#define GAME_H

#include "Board.h"

class Game{
    private:
        BOARD *gameBoard;//Pointer to the dynamic Movie structure.
        bool gOver;
        int player, comp;
    public:
        
        Game();//Constructor
        ~Game();//Destructor
        void display();//Display
        int plaMove(int *);
        int AIMove(int *);
        int upDown(int, int, int);
        int downUp(int, int, int);
        bool win(int);
        
};

#endif /* GAME_H */

