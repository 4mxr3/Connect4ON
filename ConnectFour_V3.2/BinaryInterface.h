/*
/* 
 * File:   BinaryInterface.h
 * Author: Kyle
 * Created on April 13, 2024, 1:26 PM
 * Description: Used to get and write data from binary files
 */

#ifndef BINARYINTERFACE_H
#define BINARYINTERFACE_H

#include <limits>
#include "User.h"
using namespace std;

class BinaryInterface{
private:
    string userFile = "users.bin";
    User currUser;
    int userSpot; //Users spot in binary file
    
    int findUser(fstream &, string); //Attempts to find and move the input and output stream to the user spot
    void addUser(); // Adds user that wasnt found to the binary file
    
public:
    BinaryInterface(){}
    
    int login(); //Returns 1 if admin login, 0 for user, -1 for error
    void updateRecord(int **,int); //Updated User object then writes it into binary file
    void printStats(); //Helper function to print currently loaded user data
    void adminMenu();
};

#endif /* BINARYINTERFACE_H */

