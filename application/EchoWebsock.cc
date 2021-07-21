#include "EchoWebsock.h"
#include <libserver/smart_contract/connectEthereum.h>
/**
 * @param jsonParams
 * @param done shared variable to record whether the task has been done
 * @param m mutex for editing 'done'
 * @param wsBuf streamBuf to record std::cout
 */
void performTask(boost::json::object object,const WebSocketConnectionPtr &wsConnPtr) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  auto oldBuf = std::cout.rdbuf();
  //=========================================
  //std::string json_config = "../libserver/tutorial/avarage/avarage.json";
  std::string proveing_key_path = "proving_key";
  std::string verification_key_path = "verification_key";
  std::string proof_path = "proof";
  std::string primary_input_path = "primary_input.txt";
  std::string auxiliary_input_path = "auxiliary_input.txt";

  //init json config
  //std::ifstream f(json_config);
  //std::string content((std::istreambuf_iterator<char>(f)),
  //                    std::istreambuf_iterator<char>());
  //const char *cstr = content.c_str();
  //boost::json::parser parser;
  //boost::json::error_code ec;
  //parser.write(cstr,content.size(),ec);
  //boost::json::value value = parser.release();
  //boost::json::object object = value.as_object();
  //init smart_contract and some file path to simulate the Interactive of sp,sq and op
  std::string program_str = value_to< std::string >(object["program"]);
  wsConnPtr->send("start to lock money\n");
  smart_contract::smart_contract::init();

  // sq lock their money.
  server_requester requester("0xAa3d7608ed56FCbE7aA5c75a5af180eB9Fd0133e","0xfabde6ac6b55fc46677d9453545e699b0cfe3a244a4418e357c97e6a3f56ec9d");
  printf("begin lock\n");
  assert(requester.on_lock_pay(100000)== true);
  printf("lock success\n");
  wsConnPtr->send("lock money success\n");
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
  wsConnPtr->send("start to execute user's program\n");
  auto execute_result = provider.execute_user_program(program_str,primary_input_path);
  if(execute_result.has_error()){
    boost::system::error_code ec = execute_result.error();
    fprintf(stderr,"error info : %s",ec.message().c_str());
  }
  wsConnPtr->send("success to execute user's program\n");
  wsConnPtr->send("start to generate proof\n");
  provider.on_generate_and_serialize_proof(proveing_key_path,primary_input_path,auxiliary_input_path,proof_path);
  wsConnPtr->send("success to generate proof\n");
  // op get the sp address and verify the proof.
  // if pass the proof, this process run success
  // else throw an error
  op.set_server_address(provider.get_address());
  assert(op.on_verify(verification_key_path,proof_path,primary_input_path)==true);
  printf("OK!");
  //======================================================================
  std::cout.rdbuf(oldBuf); // reset cout
}

void EchoWebsock::handleNewMessage(const WebSocketConnectionPtr &wsConnPtr,
                                   std::string &&message,
                                   const WebSocketMessageType &type) {
  //write your application logic here
  if (message.empty()) {
    wsConnPtr->send("please input your parameter");
    wsConnPtr->forceClose();
    return;
  }
  std::cout << message << endl;
//  boost::json::error_code ec;
//  auto decode_val = boost::json::parse(message, ec);
//  std::string tmp = boost::json::serialize(decode_val);
//  wsConnPtr->send("Your json:\n" + tmp);
  const char *cstr = message.c_str();
  boost::json::parser parser;
  boost::json::error_code ec;
  parser.write(cstr,message.size(),ec);
  boost::json::value value = parser.release();
  boost::json::object object = value.as_object();
  wsConnPtr->send("json format syntax: \n" + ec.message());
  if (ec.failed()) {
    wsConnPtr->forceClose();
    return;
  }
  performTask(object, wsConnPtr);
  wsConnPtr->forceClose();
}
void EchoWebsock::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr) {
  //write your application logic here
}
void EchoWebsock::handleConnectionClosed(const WebSocketConnectionPtr &wsConnPtr) {
  //write your application logic here
}