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
    int winLoss[3]; // wins vs losses vs tie
    char username[20];
    char password[20];
    int gameResult[3] = {-1,-1,-1}; //1=win, 2=loss, 3=tie, -1=no data saved
    int game[3][6][7]; // 3 different games, 6 columns, 7 rows 
     
public:
    User();
    void reset();
    
    void setUsername(string);
    string getUsername(){return username;}
    
    void setPassword(string);
    string getPassword(){return password;}
    
    void addResult(int **, int);
    void print();
    
    void write(fstream &bin){bin.write(reinterpret_cast<char *> (this), sizeof (User));}
    void read(fstream &bin){bin.read(reinterpret_cast<char *> (this), sizeof (User));}
};


#endif /* USER_H */

