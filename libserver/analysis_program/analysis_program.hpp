//
// Created by alittlehorse on 4/25/21.
//

#ifndef OSPREY_ANALYSIS_PROGRAM_HPP
#define OSPREY_ANALYSIS_PROGRAM_HPP
#include<string>
#include "Python.h"
#include <boost/outcome.hpp>
#include <boost/filesystem.hpp>
#include "analysis_err_code.hpp"
#include<iostream>
#include <sstream>
#include <fstream>
#include <utility>
//! [namespace]
namespace outcome = BOOST_OUTCOME_V2_NAMESPACE;
//! [namespace]

using namespace std;
class analysis_program {
private:
public:
    analysis_program(){}
    outcome::result<std::string> execute(string program_str,string primary_input_path) noexcept;

};



#endif //OSPREY_ANALYSIS_PROGRAM_HPP
