//
//  process.cpp
//  SDD_TASK2
//
//  Created by LIN, Winston on 20/7/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#include "process.h"

Process::Process():_pid(1), _pidLog(0){}
Process::~Process(){}

void Process::setPid(int pid){
    this->_pid = pid;
    this->_pidLog.push_back(pid);
}

int Process::getPid()const{
    return this->_pid;
}

int Process::queryPidLog(int index)const{
    return this->_pidLog.at(index);
}
