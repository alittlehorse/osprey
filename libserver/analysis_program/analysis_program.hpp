//
// Created by alittlehorse on 4/25/21.
//

#ifndef OSPREY_ANALYSIS_PROGRAM_HPP
#define OSPREY_ANALYSIS_PROGRAM_HPP
#include<string>
#include <utility>

class analysis_program {
private:
    std::string result_path;
    std::string input_path;
public:
    explicit analysis_program(std::string input_path,std::string result_path):input_path(std::move(input_path)),result_path(std::move(result_path)){}
    std::string execute();

};



#endif //OSPREY_ANALYSIS_PROGRAM_HPP
