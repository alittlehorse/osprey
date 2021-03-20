//
// Created by alittlehorse on 3/8/21.
//
#include <libserver/proof_systems/groth16_server.hpp>
#include <libserver/aux/proof_params_config.hpp>
#include <cassert>
using namespace libserver;
int main(){
    libserver::groth16_server s("avarage");
    //assert(s.get_bounds(p.get_computation_bounds_fn())!=nullopt);
    //typedef ram_tinyram<default_r1cs_gg_ppzksnark_pp> default_ram_with_pp;

    //default_r1cs_gg_ppzksnark_pp::init_public_params();

    //auto ap = s.generate_ram_architecture_params<default_ram_with_pp>(p.get_architecture_params_path());
    //assert(ap!=nullopt);
    //assert(s.generate_program(p.get_processed_assembly_path(),ap.value())!=nullopt);
    //s.construct_proof();
    s.construct_proof1();
    return 0;
}
