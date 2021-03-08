//
// Created by alittlehorse on 2/19/21.
//
#include<libserver/tinyram_complier_server.hpp>
#include<libserver/string_helper.hpp>
#include<cassert>
int main(){
    libserver::tinyram_comlier_server complier;
    std::string instr ="store.w";
    std::string s = "0 r0";
    auto a = libserver::string_helper::split(s," ");

    assert(complier.instruction_types.at(instr).size()==a.size());
    complier.complie_tinyram("avarage-complier/avarage.s");
}
