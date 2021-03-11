//
// Created by alittlehorse on 3/8/21.
//
#include <libserver/proof_systems/groth16_server.hpp>
#include <libserver/proof_program.hpp>
#include <cassert>
using namespace libserver;
int main(){
    proof_program p("avarage");
    libserver::groth16_server s(p);
    assert(s.get_bounds(p.get_computation_bounds_fn())!=nullopt);
    typedef ram_tinyram<default_r1cs_gg_ppzksnark_pp> default_ram_with_pp;

    default_r1cs_gg_ppzksnark_pp::init_public_params();

    auto ap = s.generate_ram_architecture_params<default_ram_with_pp>(p.get_architecture_params_fn());
    assert(ap!=nullopt);
    assert(s.generate_program(p.get_processed_assembly_fn(),ap.value()));
    s.construct_proof();
}
