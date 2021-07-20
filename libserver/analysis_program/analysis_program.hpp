//
// Created by alittlehorse on 4/25/21.
//

#ifndef OSPREY_ANALYSIS_PROGRAM_HPP
#define OSPREY_ANALYSIS_PROGRAM_HPP
#include<string>
#include "Python.h"
#include "analysis_err_code.hpp"
#include <boost/outcome/result.hpp>
#include<iostream>
#include <utility>
using namespace std;
class analysis_program {
private:
public:
    explicit analysis_program(){}
    boost_result<std::string> execute(string program_str) noexcept;

};



#endif //OSPREY_ANALYSIS_PROGRAM_HPP
