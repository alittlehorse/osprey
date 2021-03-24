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


bool server_provider::on_generate_and_serialize_proof() {
    s = new libserver::groth16_server(*_vp);
    r1cs_gg_ppzksnark_proving_key<default_r1cs_gg_ppzksnark_pp> pk1 ;
    std::ifstream (_vp->get_proving_key_path())>>pk1;
    auto proof = s->generate_proof(pk1);
    assert(proof!= std::nullopt);
    s->serialize_proof(*proof,_vp->get_proof_path());
    return true;
}

void server_provider::on_ready(const std::string &&config,
                               const std::string& smart_contract_address) {
    _vp = new libserver::proof_params_config(std::move(config));
    this->smart_contract_address = smart_contract_address;
}

const std::string &server_provider::get_address() {
    return smart_contract_address;
}

bool server_requester::on_generate_key_pair() {

    auto keypair = s->generate_keypair();
    assert(keypair!= std::nullopt);
    s->serialize_proveing_key(keypair.value().pk,_vp->get_proving_key_path());
    s->serialize_verification_key(keypair.value().vk,_vp->get_verification_key_path());
    return true;
}

void server_requester::on_ready(const std::string &&config,
                                const std::string& smart_contract_address,
                                const std::string& private_key){
    _vp = new libserver::proof_params_config(std::move(config));
    s = new libserver::groth16_server(*_vp);
    this->account = smart_contract_address;
    this->private_key = private_key;
}

bool osprey_plateform::on_verify() {
    auto proof = s->get_proof_from_file(_vp->get_proof_path());
    assert(proof.has_value());
    auto vk = s->get_verification_key_from_file(_vp->get_verification_key_path());
    assert(vk.has_value());
    if(s->verify(vk.value(),proof.value())){
        printf("=============================\n");
        printf("pass the proof! \n");
        printf("=============================\n");
        if(osprey_plateform::on_finish_and_pay())
            return true;
    }
    return false;
}

bool server_requester::on_lock_pay(int money) {

    //if(osprey_plateform::on_lock(money))return true;
    //else return false;
    try{
        printf("=============================================================\n");
        printf("pay......\n");
        printf("====================================================================\n");
        libserver::SendTxnTransferToContract(get_address(),get_private_key(),money);
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
    printf("=============================================================");
    printf("pay......");
    printf("====================================================================");
    libserver::SendTxnTransfer(server_address);
    return true;
}

bool osprey_plateform::on_ready(const std::string& config) {
    try{
        _vp = new libserver::proof_params_config(std::move(config));
        s = new libserver::groth16_server(*_vp);
        return true;
    }
    catch(std::exception &e){
        return false;
    }
}

void osprey_plateform::set_server_address(const string &account) {
    this->server_address = account;
}


int main(){
    server_provider provider;
    server_requester requester;
    osprey_plateform op;
//simulate sq geneate keypair;
    requester.on_ready("avarage","0xAa3d7608ed56FCbE7aA5c75a5af180eB9Fd0133e","0xfabde6ac6b55fc46677d9453545e699b0cfe3a244a4418e357c97e6a3f56ec9d");
    assert(requester.on_generate_key_pair());
    //op.submit_requester_address(sq.get_address());
    printf("begin lock\n");
    assert(requester.on_lock_pay(100000)== true);
    printf("lock success\n");
    provider.on_ready("avarage","0x57128a8c478B3fEab65866a9c39d06408c243ce9");
    provider.on_generate_and_serialize_proof();
    //
    assert(op.on_ready("avarage"));
    printf("/nplateform builed/n");
    op.set_server_address(provider.get_address());
    //
    assert(op.on_verify()==true);
    printf("OK!");
    return 0;
}