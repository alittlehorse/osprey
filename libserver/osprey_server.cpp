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

void server_provider::on_ready(const std::string &&config) {
    _vp = new libserver::proof_params_config(std::move(config));
}

bool server_requester::on_generate_key_pair() {

    auto keypair = s->generate_keypair();
    assert(keypair!= std::nullopt);
    s->serialize_proveing_key(keypair.value().pk,_vp->get_proving_key_path());
    s->serialize_verification_key(keypair.value().vk,_vp->get_verification_key_path());
    return true;
}

void server_requester::on_ready(const std::string &&config) {
    _vp = new libserver::proof_params_config(std::move(config));
    s = new libserver::groth16_server(*_vp);
}

bool server_requester::on_verify() {
    auto proof = s->get_proof_from_file(_vp->get_proof_path());
    assert(proof.has_value());
    auto vk = s->get_verification_key_from_file(_vp->get_verification_key_path());
    assert(vk.has_value());
    return s->verify(vk.value(),proof.value());
}
int main(){
    server_provider sp{};
    server_requester sq{};
//simulate sq geneate keypair;
    sq.on_ready("avarage");
    assert(sq.on_generate_key_pair());
    //
    sp.on_ready("avarage");
    sp.on_generate_and_serialize_proof();
    //
    assert(sq.on_verify()==true);
    printf("OK!");
    return 0;
}
