#include "osprey_server.hpp"
#include<filesystem>
#include <libserver/smart_contract/connectEthereum.h>

int main(){
    server_provider provider;
    server_requester requester;
    osprey_plateform op;
//simulate sq geneate keypair;

    smart_contract::smart_contract::init();

    std::string path_string{std::filesystem::current_path().parent_path().parent_path().string()};
    std::cout<<path_string+"/libserver/tutorial/avarage";

    requester.on_ready(path_string+"/libserver/tutorial/avarage","0xAa3d7608ed56FCbE7aA5c75a5af180eB9Fd0133e","0xfabde6ac6b55fc46677d9453545e699b0cfe3a244a4418e357c97e6a3f56ec9d");
    assert(requester.on_generate_key_pair());
    //op.submit_requester_address(sq.get_address());
    printf("begin lock\n");
    assert(requester.on_lock_pay(100000)== true);
    printf("lock success\n");
    provider.on_ready(path_string+"/libserver/tutorial/avarage","0x57128a8c478B3fEab65866a9c39d06408c243ce9");
    provider.on_generate_and_serialize_proof();
    //
    assert(op.on_ready(path_string+"/libserver/tutorial/avarage"));
    printf("/nplateform builed/n");
    op.set_server_address(provider.get_address());
    //
    assert(op.on_verify()==true);
    printf("OK!");
    return 0;
}