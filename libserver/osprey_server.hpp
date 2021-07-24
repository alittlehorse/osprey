/** @file
 *****************************************************************************
osprey server:
 1. server_provider class provide the server of prover(Data Seller)
 2. server_requester class provide the server of requester(Data Buyer)
*****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/
#ifndef OSPREY_OSPREY_SERVER_HPP
#define OSPREY_OSPREY_SERVER_HPP

#include<libserver/proof_systems/groth16_server.hpp>
#include <libserver/aux_struct/params_config.hpp>
#include <libserver/ram_compiler/tinyram_precompiler.hpp>
#include <libserver/analysis_program/analysis_program.hpp>


class server_provider {
 public:
  explicit server_provider(const std::string& config,const std::string& smart_contract_address);
  explicit server_provider(const boost::json::object& config,const std::string& smart_contract_address);
  bool on_generate_and_serialize_proof(const std::string& proving_key_path,const std::string& primary_input_path,const std::string& auxiliary_input_path,const std::string proof_path);
  outcome::result<std::string> execute_user_program(const std::string& program_str,const std::string& primary_input_path);
  const std::string& get_address();
 private:
  std::unique_ptr<libserver::groth16_server> groth16_server_ = nullptr;
  std::string account_;
};


class server_requester {
 public:
  explicit server_requester(const std::string& smart_contract_address,const std::string& private_key){
    this->account = smart_contract_address;
    this->private_key = private_key;};
  server_requester()=delete;
  //bool on_complier_tinyram();
  bool on_lock_pay(int money);
  const std::string& get_address();

 private:
  std::string account;
  std::string private_key;
  const std::string& get_private_key();
};

class osprey_plateform{
 private:
  std::string groth16_server_address_;
  std::unique_ptr<libserver::groth16_server> groth16_server_;
 public:
  explicit osprey_plateform(const std::string& config);
  osprey_plateform(const boost::json::object&);
  osprey_plateform()=delete;
  void set_server_address(const std::string& server_account);
  bool on_finish_and_pay();
  bool on_verify(const std::string& verifacation_key_path,const std::string& proof_path,const std::string& primary_input_path);
  bool on_generate_keypair(const std::string& proving_key_path,const std::string& verification_key_path);
};


#endif //OSPREY_OSPREY_SERVER_HPP
