//
// Created by alittlehorse on 2/14/21.
//
#include<string>
#include<libserver/ram_ppsnark_server.hpp>
#include <cassert>
using namespace libserver;
int main(){
    default_tinyram_ppzksnark_pp::init_public_params();
    libff::start_profiling();
    proof_program p("avarage1");
    ram_ppsnark_server ppsnark_server(p);
    assert(ppsnark_server.get_target_path()=="avarage1");


    const auto ap = ppsnark_server.generate_ram_ppsnark_architecture_params(p.get_architecture_params_fn());
    //load bound of the program ,include the input_size_bound,program_size_bound and time_bound;
    std::ifstream f_rp(p.get_computation_bounds_fn());
    size_t tinyram_input_size_bound1, tinyram_program_size_bound1, time_bound1;
    f_rp >> tinyram_input_size_bound1>> tinyram_program_size_bound1 >> time_bound1;

    const auto bounds =  ppsnark_server.get_bounds();
    const size_t tinyram_input_size_bound = std::get<0>(bounds);
    const size_t tinyram_program_size_bound = std::get<1>(bounds);
    const size_t time_bound = std::get<2>(bounds);
    const size_t boot_trace_size_bound = tinyram_program_size_bound + tinyram_input_size_bound;
    assert(tinyram_input_size_bound1==tinyram_input_size_bound);
    assert(boot_trace_size_bound>0);
    const boot_trace primary_input_boot_trace = ppsnark_server.generate_primary_input(ap,boot_trace_size_bound);

    auto auxiliary_input = ppsnark_server.generate_auxili_input(p.get_auxiliary_input_fn());
    assert(p.get_auxiliary_input_fn()=="avarage1/avarage1-auxiliary_input.txt");
    assert(auxiliary_input[0]==bool(1));
    auto keypair = ppsnark_server.generate_ram_ppsnark_keypair(ap,boot_trace_size_bound,time_bound);

    const auto proof2 = ppsnark_server.generate_proof(keypair,primary_input_boot_trace,auxiliary_input);
    assert(ppsnark_server.test_proof(proof2,primary_input_boot_trace,keypair)==true);
}



