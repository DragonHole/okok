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
#include <fstream>

struct User{
    size_t _passwordHash;
    
    int _score;
};

// class for login credential encryption and file manipulation

class Login{
public:
    Login();
    
    int addUser(std::string username, std::string password);
    
    bool checkCredential(std::string username, int password);
    
    void removeUser(std::string username);
    
    int retrieveScore(std::string username);
    
    void setScore(std::string username, int value);
    
    // called when the game buttons on main menu are clicked, this is supposed to run at the start but due to _loginObj is in menu class and menu class can't communicate with game class effectively(actually it can), but just deal with it...
    void readUserDetailFromFile();
    
    // called when create account button, exit button(on gameover screen) is pressed
    void writeUserDetailToFile();
    
private:
    std::map<std::string, User> _users;
};

#endif /* login_h */
