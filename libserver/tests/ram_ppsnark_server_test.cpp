//
// Created by alittlehorse on 2/14/21.
//
#include<string>
#include<libserver/ram_ppsnark_server.hpp>
#include <cassert>
using namespace libserver;
int main(){
    proof_program p("avarage");
    ram_ppsnark_server ppsnark_server(p);
    auto ;
    const auto proof = ppsnark_server.construct_proof();
    const auto ap = ppsnark_server.generate_ram_ppsnark_architecture_params(p.get_architecture_params_fn());

    std::ifstream f_rp(p.get_computation_bounds_fn());
    size_t tinyram_input_size_bound, tinyram_program_size_bound, time_bound;
    f_rp >> tinyram_input_size_bound >> tinyram_program_size_bound >> time_bound;
    const size_t boot_trace_size_bound = tinyram_program_size_bound + tinyram_input_size_bound;

    const boot_trace primary_input_boot_trace = ppsnark_server.generate_primary_input(ap,boot_trace_size_bound);
    auto auxiliary_input = ppsnark_server.generate_auxili_input(p.get_auxiliary_input_fn());

    const auto primary_input = ppsnark_server.generate_ram_ppsnark_keypair(ap,)
    ppsnark_server.test_proof(proof,)
}

