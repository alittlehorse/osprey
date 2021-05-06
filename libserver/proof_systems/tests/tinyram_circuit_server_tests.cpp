/*
 * Tests for tinyram_circuit class
 * should pass:
 * 1. tinyram_circuit initial
 *     1> bounds set right
 *     2> architecture params set right
 *     3>tinyram_program set right
 * 2. boot trace
 * 3. auxiliary input
 *     */
#include<libserver/proof_systems/tinyram_circuit.hpp>
#include <libserver/proof_systems/tinyram_r1cs_pp.hpp>

using namespace libserver;
int main(){
  typedef tinyram_r1cs_pp<tinyram_snark::default_r1cs_gg_ppzksnark_pp> params;
  std::unique_ptr<params_config> config(new params_config());
  config->init("../../libserver/tutorial/avarage/avarage.json");
  config->precompiler(config->get_verify_program());
  tinyram_circuit<params> ppp(std::move(config));
  assert(ppp.get_bounds().find("time_bound")->second==64);
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


  ppp.initial_boot_trace("../../libserver/tutorial/avarage/primary_input.txt");
  auto d = ppp.get_boot_trace();
  //printf("%d",d.get_all_trace_entries().size());
  assert(d.get_all_trace_entries().empty()==false);
  assert(d.get_all_trace_entries().size()==20);

  ppp.initial_aux_input("../../libserver/tutorial/avarage/auxiliary_input.txt");
  auto x = ppp.get_auxiliary_input_tap();
  assert(x.at(0) == 2);
  return 0;
}

