//
// Created by alittlehorse on 2/10/21.
//
#include<string>
#include<libserver/aux/proof_program.hpp>
#include <cassert>
using namespace libserver;
int main(){
     proof_program p("avarage");
     //printf(p.get_architecture_params_fn());
     std::string s= "avarage";
     assert(p.get_auxiliary_input_fn()=="avarage/avarage-auxiliary_input.txt");
     assert(p.get_assembly_fn()=="avarage/avarage.s");

}