//
// Created by alittlehorse on 2/19/21.
//
#include<libserver/tinyram_complier_server.hpp>
#include<cassert>
int main(){
    libserver::tinyram_comlier_server complier;
    assert(libserver::instruction_types.at("and").size()==3);
}
