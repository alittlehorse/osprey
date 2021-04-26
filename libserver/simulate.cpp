#include "osprey_server.hpp"
#include<filesystem>
#include <libserver/smart_contract/connectEthereum.h>

int main(){
    server_provider provider;
    server_requester requester;
    osprey_plateform op;

    //init smart_contract and some file path to simulate the Interactive of sp,sq and op
    smart_contract::smart_contract::init();
    std::string path_string{std::filesystem::current_path().parent_path().parent_path().string()};
    std::cout<<path_string+"/libserver/tutorial/avarage";

    //simulate op to generate keypair
    //verification key for sq
    //proving key for sp
    op.on_ready(path_string+"/libserver/tutorial/avarage");
    assert(op.on_generate_keypair());

    // sq is ready and lock their money. the file sq generated is located in libserver/tutorial
    requester.on_ready(path_string+"/libserver/tutorial/avarage","0xAa3d7608ed56FCbE7aA5c75a5af180eB9Fd0133e","0xfabde6ac6b55fc46677d9453545e699b0cfe3a244a4418e357c97e6a3f56ec9d");
    printf("begin lock\n");
    assert(requester.on_lock_pay(100000)== true);
    printf("lock success\n");

    // sp is ready for zkp .
    // sp generate the proof and serialize it in local. the proof is local on libserver/tutorial/proof
    provider.on_ready(path_string+"/libserver/tutorial/avarage","0x57128a8c478B3fEab65866a9c39d06408c243ce9");
    provider.on_generate_and_serialize_proof();

    // op get the sp address and verify the proof.
    // if pass the proof, this process run success
    // else throw an error
    assert(op.on_ready(path_string+"/libserver/tutorial/avarage"));
    printf("/nplateform builed/n");
    op.set_server_address(provider.get_address());
    assert(op.on_verify()==true);
    printf("OK!");
    return 0;
}