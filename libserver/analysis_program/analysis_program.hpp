//
// Created by alittlehorse on 4/25/21.
//

#ifndef OSPREY_ANALYSIS_PROGRAM_HPP
#define OSPREY_ANALYSIS_PROGRAM_HPP
#include<string>
#include "Python.h"
#include<iostream>
#include <utility>
using namespace std;
class analysis_program {
private:
public:
    explicit analysis_program(){}
    std::string execute(string program_str);

};



#endif //OSPREY_ANALYSIS_PROGRAM_HPP
