/** @file
 *****************************************************************************
tests for groth16 server
 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/


#include <libserver/proof_systems/groth16_server.cpp>
#include <libserver/aux_struct/proof_params_config.hpp>
#include <libserver/aux_struct/params_config.hpp>
#include <cassert>
#include <filesystem>
using namespace std::filesystem;
using namespace libserver;
int main(){
  std::string proveing_key_path = "../../libserver/tutorial/avarage/proving_key";
  std::string verification_key_path = "../../libserver/tutorial/avarage/verification_key";
  std::string proof_path = "../../libserver/tutorial/avarage/proof";
  std::unique_ptr<params_config> config(new params_config());
  config->init("../../libserver/tutorial/avarage/avarage.json");
  config->precompiler(config->get_verify_program());
  libserver::groth16_server s(std::move(config));
  //test keypair
  auto keypair = s.generate_keypair().value();
  assert(s.serialize_proveing_key(keypair.pk,proveing_key_path));
  auto pk1 = s.get_proving_key_from_file(proveing_key_path);
  assert(pk1.has_value());
  assert(pk1.value()==keypair.pk);
  assert(s.serialize_verification_key(keypair.vk,verification_key_path));
  auto vk1 = s.get_verification_key_from_file(verification_key_path);
  assert(vk1.has_value());
  assert(vk1.value()==keypair.vk);
  //test proof
  auto proof = s.generate_proof(pk1.value(),"../../libserver/tutorial/avarage/primary_input.txt","../../libserver/tutorial/avarage/auxiliary_input.txt");
  assert(proof!=std::nullopt);
  assert(s.serialize_proof(proof.value(),proof_path));
  auto proof1 = s.get_proof_from_file(proof_path);
  assert(proof1.value() == proof.value());

  bool b = s.verify(keypair.vk,proof.value(),"../../libserver/tutorial/avarage/primary_input.txt");
  assert(b== true);
  return 0;
}
