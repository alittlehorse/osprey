//
// Created by alittlehorse on 3/16/21.
//
#include<libserver/proof_systems/proof_public_params.hpp>
#include<tinyram_snark/common/default_types/tinyram_gg_ppzksnark_pp.hpp>
int main(){
    libserver::proof_public_params<tinyram_snark::default_r1cs_gg_ppzksnark_pp> ppp("avarage/avarage-processed_assembly.txt",
                                                                                    "avarage/avarage-computation_bounds.txt",
                                                                                    "avarage/avarage-architecture_params.txt",
                                                                                    "avarage/avarage-primary_input.txt");

    const int a = ppp.get_bounds().find("time_bound")->second;
    assert(a==64);
    auto b = ppp.get_ram_architecture_params();
    assert(b.w==16);
    if(!std::is_same<decltype(b),tinyram_snark::ram_architecture_params<tinyram_snark::default_tinyram_gg_ppzksnark_pp::machine_pp>>::value){
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
    return 0;
}

