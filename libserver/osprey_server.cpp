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


void server_requester::on_ready(const std::string &&config,
                                const std::string& smart_contract_address,
                                const std::string& private_key){
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
    smart_contract::smart_contract::SendTxnTransfer(server_address);
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

bool osprey_plateform::on_generate_keypair() {
    auto keypair = s->generate_keypair();
    if(keypair== std::nullopt) return false;
    s->serialize_proveing_key(keypair.value().pk,_vp->get_proving_key_path());
    s->serialize_verification_key(keypair.value().vk,_vp->get_verification_key_path());
    return true;
}


