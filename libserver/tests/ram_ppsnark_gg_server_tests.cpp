//
// Created by alittlehorse on 3/8/21.
//
#include <libserver/proof_systems/ram_gg_ppsnark_server.hpp>
#include <libserver/proof_program.hpp>
#include <cassert>
using namespace libserver;
int main(){
    proof_program p("avarage");
    libserver::ram_gg_ppsnark_server s(p);
    s.construct_proof();
}
