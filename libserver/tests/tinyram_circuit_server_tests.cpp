//
// Created by alittlehorse on 3/16/21.
//
#include<libserver/proof_systems/tinyram_circuit.hpp>
#include<tinyram_snark/common/default_types/tinyram_gg_ppzksnark_pp.hpp>
#include <libserver/proof_systems/tinyram_r1cs_pp.hpp>

using namespace libserver;
int main(){
    typedef tinyram_r1cs_pp<tinyram_snark::default_r1cs_gg_ppzksnark_pp> params;
    tinyram_circuit<params> ppp("avarage/avarage-processed_assembly.txt",
                                "avarage/avarage-computation_bounds.txt",
                                "avarage/avarage-architecture_params.txt",
                                "avarage/avarage-primary_input.txt");

    const int a = ppp.get_bounds().find("time_bound")->second;
    assert(a==64);
    auto b = ppp.get_ram_architecture_params();
    assert(b.w==16);
    if(!std::is_same<decltype(b),tinyram_snark::ram_architecture_params<params::machine_pp>>::value){
        return -1;
    }
    auto c = ppp.get_tinyram_program();
    if(!std::is_same<decltype(c),tinyram_snark::tinyram_program>::value){
        return -1;
    }
    assert(c.size()==19);
    auto d = ppp.get_boot_trace();
    //printf("%d",d.get_all_trace_entries().size());
    assert(d.get_all_trace_entries().empty()==false);
    assert(d.get_all_trace_entries().size()==20);
    return 0;
}

