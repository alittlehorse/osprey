//
// Created by alittlehorse on 2/19/21.
//
#include<libserver/ram_complier/tinyram_complier_server.hpp>
#include<libserver/aux/string_helper.hpp>


#include<cassert>
int main(){
    libserver::tinyram_comlier_server complier;
    std::string instr ="store.w";
    std::string s = "0 r0";
    auto a = libserver::string_helper::split(s," ");

    assert(complier.complie_tinyram("avarage-complier/avarage.s","avarage-processed_assembly.txt")==true);
    auto b = complier.complie_r1cs<libff::default_ec_pp>("avarage-complier/avarage-architecture_params.txt","avarage-complier/avarage-computation_bounds.txt");

    assert(b!=nullopt);
}
