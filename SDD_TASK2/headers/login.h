//
//  login.h
//  SDD_TASK2
//
//  Created by LIN, Winston on 29/7/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#ifndef login_h
#define login_h

#include <map>
#include <string>
#include <functional>
#include <iostream>

struct User{
    size_t _passwordHash;
    
    int _score;
};

// class for login credential encryption and file manipulation

class Login{
public:
    Login();
    
    void addUser(std::string username, int password);
    
    bool checkCredential(std::string username, int password);
    
    void removeUser(std::string username);
    
    int retrieveScore(std::string username);
    
    void setScore(std::string username, int value);
    
private:
    std::map<std::string, User> _users;
};

#endif /* login_h */
