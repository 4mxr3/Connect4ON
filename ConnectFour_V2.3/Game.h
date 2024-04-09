
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
        BOARD *gameBoard;
        bool gOver;
        int player, comp, pMove;
    public:
        
        Game();//Constructor
        ~Game();//Destructor
        void display();//Display
        int plaMove(int *,int);
        int AIMove(int *);
        int upDown(int, int, int);
        int downUp(int, int, int);
        bool win(int);
        void playerVsPlayer();
        void playerVsComputer();
};

#endif /* GAME_H */

