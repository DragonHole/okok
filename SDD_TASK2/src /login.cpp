//
//  login.cpp
//  SDD_TASK2
//
//  Created by LIN, Winston on 29/7/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#include "login.h"
#include <vector>

Login::Login(){}

void Login::addUser(std::string username, std::string password){
    std::hash<std::string> hash;
    size_t passwordHash = hash(password);
    std::cout<<"received password: "<<password<<std::endl;
    std::cout<<"hash created:"<<passwordHash<<std::endl;
    
    if(this->_users.count(username) == 0)
        this->_users[username]._passwordHash = passwordHash;
    else
        std::cerr<<"\n couldn't create account, user "<<username<<" already existed"<<std::endl;
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

void Login::writeUserDetailToFile(){
    std::ofstream ostream("users.txt");
    
    // if can't open file then exit
    if(!ostream){
        std::cerr<<"\n error opening user.txt"<<std::endl;
        exit(1);
    }

    std::map<std::string, User>::iterator it;
    
    for(it = this->_users.begin(); it != this->_users.end(); it++){
        ostream<<it->first<<" "<<it->second._passwordHash<<" "<<it->second._score<<std::endl;
    }
}

void Login::readUserDetailFromFile(){
    std::ifstream istream("users.txt");
    
    // clear map before entering new data, avoid conflict...
    this->_users.clear();
    
    // temporary variables
    std::string username;
    size_t password;
    int score;
    
    while(istream>>username && istream>>password && istream>>score){
        this->_users[username]._passwordHash = password;
        this->_users[username]._score = score;
    }
}
