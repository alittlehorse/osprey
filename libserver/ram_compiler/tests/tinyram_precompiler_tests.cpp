//
// Created by alittlehorse on 2/19/21.
//
#include<libserver/ram_compiler/tinyram_precompiler.hpp>
#include<libserver/aux_struct/string_helper.hpp>
#include<tinyram_snark/common/default_types/r1cs_gg_ppzksnark_pp.hpp>
#include<libserver/aux_struct/params_config.hpp>

#include<cassert>
int main(){
  libserver::tinyram_precompiler complier;
  std::string instr ="store.w";
  std::string s = "0 r0";
  auto a = libserver::string_helper::split(s," ");

  assert(complier.complie_tinyram("avarage-complier/avarage.s","avarage-processed_assembly.txt")==true);
  bool b = complier.complie_tinyram("avarage-complier/avarage-architecture_params.txt","avarage-complier/avarage-computation_bounds.txt");
  assert(b== true);
  auto c = params_config();
  c.init("../../libserver/tutorial/avarage/avarage.json");
  std::string s1;
  assert(complier.compile_tinyram(c.get_verify_program(),&s1));
  printf("%s",s1.c_str());
}
