#include <libserver/osprey_server.hpp>
#include <libserver/smart_contract/connectEthereum.h>
#include <filesystem>
#include <boost/json.hpp>
int main(){
  std::string config = "../config.json";
  std::ifstream f_config(config);
  std::string conf_content((std::istreambuf_iterator<char>(f_config)),
                      std::istreambuf_iterator<char>());
  const char *conf_cstr = conf_content.c_str();
  printf("%s",conf_cstr);
  boost::json::parser conf_parser;
  boost::json::error_code conf_ec;
  conf_parser.write(conf_cstr,conf_content.size(),conf_ec);
  if(conf_ec) exit(1);
  boost::json::object config_object = conf_parser.release().as_object();
  std::string folder_path = value_to<std::string>(config_object.at("middle_folder"));
  std::string json_config = folder_path + value_to<std::string>(config_object.at("proof_config_name"));
  std::string proveing_key_path = folder_path + value_to<string>(config_object.at("proving_key_name"));
  std::string verification_key_path = folder_path + value_to<string>(config_object.at("verification_key_name"));
  std::string proof_path = folder_path + value_to<string>(config_object.at("proof_name"));
  std::string primary_input_path = folder_path + value_to<string>(config_object.at("primary_input_file_name"));
  std::string auxiliary_input_path = folder_path + value_to<string>(config_object.at("auxiliary_input_file_name"));
  printf("%s",json_config.c_str());
  //=====================================
//  std::string json_config = "/usr/tests/avarage/avarage.json";
//  std::string proveing_key_path = "/usr/tests/avarage/proving_key";
//  std::string verification_key_path = "/usr/tests/avarage/verification_key";
//  std::string proof_path = "/usr/tests/avarage/proof";
//  std::string primary_input_path = "/usr/tests/avarage/primary_input.txt";
//  std::string auxiliary_input_path = "/usr/tests/avarage/auxiliary_input.txt";
  //init json config
  std::ifstream f("/home/alittlehorse/ProjectHUB/github.com/osprey-dev/libserver/tutorial/avarage/avarage.json");
  std::string content((std::istreambuf_iterator<char>(f)),
                      std::istreambuf_iterator<char>());
  const char *cstr = content.c_str();
  printf("%s\n",cstr);
  boost::json::parser parser;
  boost::json::error_code ec;
  parser.write(cstr,content.size(),ec);
  if(ec) exit(1);
  boost::json::value value = parser.release();
  boost::json::object object = value.as_object();



  //init smart_contract and some file path to simulate the Interactive of sp,sq and op
  smart_contract::smart_contract::init();

  // sq lock their money.
  server_requester requester("0xAa3d7608ed56FCbE7aA5c75a5af180eB9Fd0133e","0xfabde6ac6b55fc46677d9453545e699b0cfe3a244a4418e357c97e6a3f56ec9d");
  printf("begin lock\n");
  assert(requester.on_lock_pay(100000)== true);
  printf("lock success\n");

  //simulate op to generate keypair
  //verification key for sq
  //proving key for sp
  osprey_plateform op(object);
  assert(op.on_generate_keypair(proveing_key_path,verification_key_path));
  printf("=====================================\n");
  printf("\nplateform builed\n");
  printf("=====================================\n");
  // sp is ready for zkp .
  // sp generate the proof and serialize it in local. the proof is local on libserver/tutorial/proof
  server_provider provider(object,"0x57128a8c478B3fEab65866a9c39d06408c243ce9");
  bool flag = provider.on_generate_and_serialize_proof(proveing_key_path,primary_input_path,auxiliary_input_path,proof_path);
  if(!flag){
    std::cout<< filesystem::current_path()<<endl;
    printf("please check the auxiliary_input file path and proof_input file path!\n");
    printf("the auxiliary input file path in this processing is on %s\n the prima"
           "ry input file path in this processing is on%s",auxiliary_input_path.c_str(),primary_input_path.c_str());
    exit(1);
  }

  // op get the sp address and verify the proof.
  // if pass the proof, this process run success
  // else throw an error
  op.set_server_address(provider.get_address());
  assert(op.on_verify(verification_key_path,proof_path,primary_input_path)==true);
  printf("OK!");

  return 0;
}