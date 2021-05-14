#include <libserver/osprey_server.hpp>
#include <libserver/smart_contract/connectEthereum.h>

int main(){
  //std::string json_config = "../libserver/tutorial/avarage/avarage.json";
  std::string proveing_key_path = "../libserver/tutorial/avarage/proving_key";
  std::string verification_key_path = "../libserver/tutorial/avarage/verification_key";
  std::string proof_path = "../libserver/tutorial/avarage/proof";
  std::string primary_input_path = "../libserver/tutorial/avarage/primary_input.txt";
  std::string auxiliary_input_path = "../libserver/tutorial/avarage/auxiliary_input.txt";
  //init json config
  std::ifstream f(json_config);
  std::string content((std::istreambuf_iterator<char>(f)),
                      std::istreambuf_iterator<char>());
  const char *cstr = content.c_str();
  boost::json::parser parser;
  boost::json::error_code ec;
  parser.write(cstr,content.size(),ec);
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
  printf("=====================================");
  printf("\nplateform builed\n");
  printf("=====================================");
  // sp is ready for zkp .
  // sp generate the proof and serialize it in local. the proof is local on libserver/tutorial/proof
  server_provider provider(object,"0x57128a8c478B3fEab65866a9c39d06408c243ce9");

  provider.on_generate_and_serialize_proof(proveing_key_path,primary_input_path,auxiliary_input_path,proof_path);

  // op get the sp address and verify the proof.
  // if pass the proof, this process run success
  // else throw an error
  op.set_server_address(provider.get_address());
  assert(op.on_verify(verification_key_path,proof_path,primary_input_path)==true);
  printf("OK!");

  return 0;
}