/** @file
 *****************************************************************************
osprey server:
 1. server_provider class provide the server of prover(Data Seller)
 2. server_requester class provide the server of requester(Data Buyer)

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/

#include "osprey_server.hpp"
#include <libserver/smart_contract/connectEthereum.h>

/*
 * Given proving_key_path,primary_input_path,auxiliary_input_path
 * Generate proof and serialize proof in proof path
 */
bool server_provider::on_generate_and_serialize_proof(const std::string& proving_key_path,const std::string& primary_input_path,const std::string& auxiliary_input_path,const std::string proof_path) {
  if(!filesystem::exists(proving_key_path)){
    fprintf(stderr,"proving_key_path(%s) does not exists\n",proving_key_path.c_str());
  }
  if(!filesystem::exists(primary_input_path)){
    fprintf(stderr,"primary_input_path(%s) does not exists\n",primary_input_path.c_str());
  }
  if(!filesystem::exists(auxiliary_input_path)){
    fprintf(stderr,"auxiliary_input_path(%s) does not exists\n",auxiliary_input_path.c_str());
  }
  if(!filesystem::exists(proof_path)){
    fprintf(stderr,"proof_path(%s) does not exists\n",proof_path.c_str());
  }
  r1cs_gg_ppzksnark_proving_key<default_r1cs_gg_ppzksnark_pp> pk1 ;
  try{
    std::ifstream (proving_key_path)>>pk1;
  }
catch(std::exception& e){
  printf("the proving file path is not right!\n");
  return false;
}
  auto proof = groth16_server_->generate_proof(pk1,primary_input_path,auxiliary_input_path);
  assert(proof!= std::nullopt);
  groth16_server_->serialize_proof(proof.value(),proof_path);
  return true;
}

outcome::result<std::string> server_provider::execute_user_program(
    const string& program_str, const string& primary_input_path) {
  analysis_program analysisProgram;
  auto res = analysisProgram.execute(program_str,primary_input_path);
  return res;
}

server_provider::server_provider(const boost::json::object& config,const std::string& smart_contract_address){
  std::unique_ptr<params_config> a= std::make_unique<params_config>(config);
  a->precompiler(a->get_verify_program());
  groth16_server_ = make_unique<libserver::groth16_server>(std::move(a));
  account_ = smart_contract_address;
}
server_provider::server_provider(const std::string &config,
                               const std::string& smart_contract_address) {
  std::unique_ptr<params_config> a = std::make_unique<params_config>();
  a->init(config);
  a->precompiler(a->get_verify_program());
  this->groth16_server_= std::make_unique<libserver::groth16_server>(std::move(a));
  this->account_ = smart_contract_address;
}

const std::string &server_provider::get_address() {
  return account_;
}

bool osprey_plateform::on_verify(const std::string& verifacation_key_path,const std::string& proof_path,const std::string& primary_input_path) {
  auto vk = groth16_server_->get_verification_key_from_file(verifacation_key_path);
  assert(vk.has_value());
  auto proof = groth16_server_->get_proof_from_file(proof_path);
  assert(proof.has_value());
  if(groth16_server_->verify(vk.value(),proof.value(),primary_input_path)){
    printf("=============================\n");
    printf("pass the proof! \n");
    printf("=============================\n");
    if(osprey_plateform::on_finish_and_pay())
      printf("=============================================\n");
    printf("pay success\n");
    printf("=============================================\n");
    return true;

  }
  else{
    printf("=============================================\n");
    printf("pay failed!\n");
    printf("=============================================\n");
    return true;
  }
  return false;
}

bool server_requester::on_lock_pay(int money) {
  //if(osprey_plateform::on_lock(money))return true;
  //else return false;
  try{
    printf("=============================================================\n");
    printf("locking......\n");
    printf("====================================================================\n");
    smart_contract::smart_contract::SendTxnTransferToContract(get_address(),get_private_key(),money);
    return true;
  }
  catch(std::exception &e){
    return false;
  }
}


const std::string& server_requester::get_address() {
  return account;
}

const std::string &server_requester::get_private_key() {
  return private_key;
}


bool osprey_plateform::on_finish_and_pay() {
  printf("=============================================================\n");
  printf("pay......\n");
  printf("====================================================================\n");
  smart_contract::smart_contract::SendTxnTransfer(groth16_server_address_);
  return true;
}

osprey_plateform::osprey_plateform(const std::string& config) {
  std::unique_ptr<params_config> a= std::make_unique<params_config>();
  a->init(config);
  a->precompiler(a->get_verify_program());
  groth16_server_ = make_unique<libserver::groth16_server>(std::move(a));
}

osprey_plateform::osprey_plateform(const boost::json::object &object) {
  std::unique_ptr<params_config> a= std::make_unique<params_config>(object);
  a->precompiler(a->get_verify_program());
  groth16_server_ = make_unique<libserver::groth16_server>(std::move(a));
}

void osprey_plateform::set_server_address(const string &account) {
  this->groth16_server_address_ = account;
}
/*
 * generate verification key and proof key
 * no need to know the primary input and auxiliary input
 * */
bool osprey_plateform::on_generate_keypair(const std::string& proving_key_path,const std::string& verification_key_path) {
  auto keypair = groth16_server_->generate_keypair();
  if(keypair== std::nullopt) return false;
  if(!groth16_server_->serialize_proveing_key(keypair.value().pk,proving_key_path)){
    exit(1);
  };
  if(!groth16_server_->serialize_verification_key(keypair.value().vk,verification_key_path)){
    exit(1);
  }
  return true;
}



