#include "BinaryInterface.h"

void BinaryInterface::login(){
    string username;
    
    cout << "Enter username: ";
    cin >> username;
    
    fstream bin(userFile, ios::in | ios::out | ios::binary);
    userSpot = findUser(bin,username);//Save userspot for overwriting
    bin.close();
    
    //User was not found, add them to the file
    if (userSpot == -1){
        currUser.setUsername(username);
        addUser();
    }
}

void BinaryInterface::printStats(){
    currUser.print();
}

void BinaryInterface::updateRecord(int **b, int r){
    //Update result in User object
    currUser.addResult(b,r);
    
    //Find spot of currUser in binary file and overwrite that data
    fstream bin(userFile, ios::in | ios::out | ios::binary);
    long cursor = userSpot * sizeof(User);
    bin.seekp(cursor, ios::beg);
    currUser.write(bin);
    
    bin.close();
}


int BinaryInterface::findUser(fstream &bin, string username){
    bin.seekg(0, ios::beg); //move read cursor to the beginning
    int count = -1;
    
    //Read in users from the binary file until you find the matching username or 
    //reach the end of the file
    while(username != currUser.getUsername() && !bin.eof()){
        currUser.read(bin);
        count++;
    }
    
    if (bin.eof() && username != currUser.getUsername()){
        return -1; //If user not found, return -1
    }
    
    return count; //if user is found, return the record location
}

void BinaryInterface::addUser(){
    //Reset all read data in user object besides username
    string temp = currUser.getUsername();
    currUser.reset();
    currUser.setUsername(temp);
    
    //Write this new data to binary file
    fstream bin(userFile, ios::out | ios::binary | ios::app); //Open file in append mode
    currUser.write(bin);
    bin.close();
    
    //Reset object and find record to save new userSpot
    fstream bin2(userFile, ios::in | ios::binary);
    currUser.reset();
    userSpot = findUser(bin2,temp);
    bin2.close();
}