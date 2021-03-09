#include <libserver/proof_systems/ram_ppsnark_server.hpp>

using namespace libserver;

int main()
{
    //simulate the server provider take the program send by server requester
    libserver::proof_program p("avarage");
    libserver::ram_ppsnark_server server(p);
    //simulate the trust third part to construct the keypair and architecture params
    auto arch_params = server.generate_ram_ppsnark_architecture_params(p.get_architecture_params_fn());
    const auto bounds =  server.get_bounds();
    const size_t tinyram_input_size_bound = std::get<0>(bounds);
    const size_t tinyram_program_size_bound = std::get<1>(bounds);
    const size_t time_bound = std::get<2>(bounds);
    const size_t boot_trace_size_bounds = tinyram_input_size_bound+tinyram_program_size_bound;
    const auto primary_input  = server.generate_primary_input(arch_params,boot_trace_size_bounds);
    const auto keypair = server.generate_ram_ppsnark_keypair(arch_params,boot_trace_size_bounds,time_bound);
    //then the thired part send the keypair to requester and provider.

    //simulate the proof privider to generate the proof
    auto aux = server.generate_auxili_input();
    const proof myproof = server.generate_proof(keypair,primary_input,aux);

    //simulate the request verify thei proof;
    if(server.test_proof(myproof,primary_input,keypair))printf("pass the proof");
    else{printf("fail!");}


}
