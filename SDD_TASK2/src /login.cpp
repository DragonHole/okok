//
//  login.cpp
//  SDD_TASK2
//
//  Created by LIN, Winston on 29/7/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#include "login.h"

Login::Login(){}

void Login::addUser(std::string username, int password){
    std::hash<int> hash;
    size_t passwordHash = hash(password);
    std::cout<<"hash created:"<<passwordHash<<std::endl;
    
    this->_users[username]._passwordHash = passwordHash;
}

bool Login::checkCredential(std::string username, int password){
    std::hash<int> hash;
    size_t passwordHash = hash(password);
    
    if(this->_users.count(username) == 0)
        std::cout<<"User "<<username<<" not found in database";
    
    // still return result even if user not present
    return (this->_users[username]._passwordHash == passwordHash);
}


int Login::retrieveScore(std::string username){
    return this->_users[username]._score;
}

void Login::setScore(std::string username, int value){
    this->_users[username]._score = value;
}

void Login::removeUser(std::string username){
    this->_users.erase(username);
}
