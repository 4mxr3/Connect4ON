/* 
 * File:   User.h
 * Author: Kyle
 * Created on April 13, 2024, 1:18 PM
 * Description: Class to hold all info for users
 */

#ifndef USER_H
#define USER_H


#include <string>
#include <fstream>
#include <iostream>
#include <string.h>
using namespace std;

class User{
private:
    char username[20];
    int gameResult[3] = {-1,-1,-1}; //1=win, 2=loss, 3=tie, -1=no data saved
    int game[3][7][6]; // 3 different games, 7 columns, 6 rows 
    int winLoss[3]; // wins vs losses vs tie
    
public:
    User();
    void reset();
    
    void setUsername(string);
    string getUsername(){return username;}
    
    void addResult(int **, int);
    void print();
    
    void write(fstream &bin){bin.write(reinterpret_cast<char *> (this), sizeof (User));}
    void read(fstream &bin){bin.read(reinterpret_cast<char *> (this), sizeof (User));}
};


#endif /* USER_H */

