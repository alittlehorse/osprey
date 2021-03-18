//
// Created by alittlehorse on 3/18/21.
//
#include <libserver/proof_systems/r1cs_adapter.hpp>
#include <libserver/proof_systems/tinyram_r1cs_pp.hpp>
using namespace libserver;
int main(){
    r1cs_adapter<tinyram_r1cs_pp<tinyram_snark::default_r1cs_gg_ppzksnark_pp>> ra("avarage");
}
