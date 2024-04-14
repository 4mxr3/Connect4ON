/* 
 * File:   Board.h
 * Author: Janaye Jackson
 *
 * Created on March 22, 2024, 11:40 AM
 */

#ifndef BOARD_H
#define BOARD_H

struct BOARD
{
    int row, col;
    int **game; // a standard connect four game is 6 x 7
};

#endif /* BOARD_H */

