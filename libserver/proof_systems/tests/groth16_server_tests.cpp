/** @file
 *****************************************************************************
tests for groth16 server
 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/


#include <libserver/proof_systems/groth16_server.hpp>
#include <libserver/aux_struct/proof_params_config.hpp>
#include <cassert>
#include <filesystem>
using namespace std::filesystem;
using namespace libserver;
int main(){
    std::string path_string{std::filesystem::current_path().parent_path().parent_path().string()};
    proof_params_config _vp(path_string+("/libserver/tutorial/avarage"));
    libserver::groth16_server s(_vp);
    auto keypair = s.generate_keypair().value();
    assert(s.serialize_proveing_key(keypair.pk,_vp.get_proving_key_path()));
    auto pk1 = s.get_proving_key_from_file(_vp.get_proving_key_path());
    assert(pk1.has_value());
    assert(pk1.value()==keypair.pk);
    assert(s.serialize_verification_key(keypair.vk,_vp.get_verification_key_path()));
    auto vk1 = s.get_verification_key_from_file(_vp.get_verification_key_path());
    assert(vk1.has_value());
    assert(vk1.value()==keypair.vk);

    auto proof = s.generate_proof(pk1.value());
    assert(proof!=std::nullopt);
    assert(s.serialize_proof(proof.value(),_vp.get_proof_path()));
    auto proof1 = s.get_proof_from_file(_vp.get_proof_path());
    assert(proof1.value() == proof.value());
    bool b = s.verify(keypair.vk,proof.value());
    assert(b== true);
    return 0;
}
