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
                                const std::string& smart_contract_address){
    _vp = new libserver::proof_params_config(std::move(config));
    s = new libserver::groth16_server(*_vp);
    this->smart_contract_address = smart_contract_address;
}

bool server_requester::on_verify() {
    auto proof = s->get_proof_from_file(_vp->get_proof_path());
    assert(proof.has_value());
    auto vk = s->get_verification_key_from_file(_vp->get_verification_key_path());
    assert(vk.has_value());
    if(s->verify(vk.value(),proof.value())){
        if(osprey_plateform::on_finish_and_pay())
            return true;
    }
    return false;
}

bool server_requester::on_lock_pay(double money) {
    if(osprey_plateform::on_lock(money))return true;
    else return false;
}


const std::string& server_requester::get_address() {
    return smart_contract_address;
}

const std::string &osprey_plateform::get_address() {
    return plateform_address;
}

void osprey_plateform::submit_requester_address(const std::string & requester_address) {
    this->requester_address = requester_address;
}

void osprey_plateform::submit_server_address(const std::string &server_address) {
    this->server_address = server_address;
}

bool osprey_plateform::on_lock(double lock_money) {
    lock_money = lock_money;
    //TODO:smart_contract:translate mony from requester to plateform address
}

bool osprey_plateform::on_finish_and_pay() {
    //TODO: smart contract: translate mony from plateform address to server address
}


int main(){
    server_provider sp;
    server_requester sq;
    osprey_plateform op;
//simulate sq geneate keypair;
    sq.on_ready("avarage");
    assert(sq.on_generate_key_pair());
    op.submit_requester_address(sq.get_address());
    sq.on_lock_pay(0.3);
    //
    sp.on_ready("avarage");
    sp.on_generate_and_serialize_proof();
    //
    op.submit_server_address(sp.get_address());
    //
    assert(sq.on_verify()==true);
    printf("OK!");
    return 0;
}