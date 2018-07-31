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

int Login::addUser(std::string username, std::string password){
    std::hash<std::string> hash;
    size_t passwordHash = hash(password);
    int result;
    
    if(this->_users.count(username) != 0)
        result = 1;
    else if(strlen(username.c_str()) == 0 && strlen(password.c_str()) > 0)
        result = 2;
    else if(strlen(password.c_str()) == 0 && strlen(username.c_str()) > 0)
        result = 3;
    else if((strcmp(username.c_str(), password.c_str()) == 0) && strlen(password.c_str()) > 0 && strlen(username.c_str()) > 0)
        result = 4;
    else if(strlen(username.c_str()) == 0 && strlen(password.c_str()) == 0)
        result = 5;
    
    else{
        this->_users[username]._passwordHash = passwordHash;
        result = 0;
    }
    
    return result;
}

int Login::checkCredential(std::string username, std::string password){
    std::hash<std::string> hash;
    size_t passwordHash = hash(password);
    int result;
    
    if(username.empty() && password.empty())
        result = 5;
    else if(username.empty() && !password.empty())
        result = 3;
    else if(!username.empty() && password.empty())
        result = 4;
    else if (this->_users.count(username) == 0)
        result = 2;
    else if(passwordHash != this->_users[username]._passwordHash)
        result = 6;

    else if(passwordHash == this->_users[username]._passwordHash){
        this->_users[username]._passwordHash = passwordHash;
        result = 1;
    }
    
    return result;
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
    std::cout<<"\nwritten to file"<<std::endl;
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
        std::cout<<"Loaded user: "<<username<<" with Password: "<<password<<" and score "<<score<<std::endl;
    }
}
