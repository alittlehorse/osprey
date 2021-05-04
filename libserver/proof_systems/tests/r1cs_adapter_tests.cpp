//
// Created by alittlehorse on 3/18/21.
//
#include <libserver/proof_systems/r1cs_adapter.hpp>
#include <libserver/proof_systems/tinyram_r1cs_pp.hpp>
#include <libserver/aux_struct/params_config.hpp>
using namespace libserver;
int main(){
  typedef tinyram_r1cs_pp<tinyram_snark::default_r1cs_gg_ppzksnark_pp> params;
  std::unique_ptr<params_config> config(new params_config());
  config->init("../../libserver/tutorial/avarage/avarage.json");
  r1cs_adapter<params> ra(std::move(config));
  return 0;
}
