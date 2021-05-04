/** @file
 *****************************************************************************

the server of zksnark using the Groth16 algorithm
 + generate_proof
 + test_proof
 + generate keypair
 + generate architecture params
 + get bounds(time bounds, compution bounds...)

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/


#ifndef OSPREY_GROTH16_SERVER_TCC_
#define OSPREY_GROTH16_SERVER_TCC_

#include <libserver/aux_struct/Log.hpp>
#include <tuple>
#include <tinyram_snark/common/default_types/tinyram_gg_ppzksnark_pp.hpp>
#include <tinyram_snark/zk_proof_systems/r1cs_gg_ppzksnark/r1cs_gg_ppzksnark.hpp>
#include <libserver/proof_systems/groth16_server.hpp>


using namespace tinyram_snark;
namespace  libserver{

    std::optional<const r1cs_gg_ppzksnark_proof<default_r1cs_gg_ppzksnark_pp>>
    groth16_server::generate_proof(const r1cs_gg_ppzksnark_proving_key<default_r1cs_gg_ppzksnark_pp>& proving_key) {
        try{
            const r1cs_gg_ppzksnark_proof<tinyram_r1cs_params::snark_pp>
                    proof = r1cs_gg_ppzksnark_prover<tinyram_r1cs_params::snark_pp>(proving_key,
                                                                                    r1cs_adapter_->get_r1cs_primary_input(),
                                                                                    r1cs_adapter_->get_auxiliary_input());
            return {proof};
        }
       catch (std::exception &e){
           return std::nullopt;
       }
    }

    std::optional<const r1cs_gg_ppzksnark_keypair<default_r1cs_gg_ppzksnark_pp>> groth16_server::generate_keypair() {
        try{
            auto keypair = r1cs_gg_ppzksnark_generator<tinyram_r1cs_params::snark_pp>(r1cs_adapter_->get_r1cs_constraint_system());//OK!
            return {keypair};
        }
       catch (std::exception &e){
           return std::nullopt;
       }
    }
    bool groth16_server::verify(const r1cs_gg_ppzksnark_verification_key<default_r1cs_gg_ppzksnark_pp>& verification_key,
                                const r1cs_gg_ppzksnark_proof<default_r1cs_gg_ppzksnark_pp>& proof){
        bool b = r1cs_gg_ppzksnark_verifier_strong_IC<tinyram_r1cs_params::snark_pp>(verification_key, r1cs_adapter_->get_r1cs_primary_input(), proof);
        return b;
    }

    bool groth16_server::serialize_proveing_key(const r1cs_gg_ppzksnark_proving_key<default_r1cs_gg_ppzksnark_pp>& proving_key,
                                                const std::string& proving_key_path) {
        std::ofstream proving_key_file(proving_key_path,std::ios::out|std::ios::binary);
        try{
            proving_key_file<<proving_key;
            return true;
        }
        catch (std::exception &e){
            return false;
        }
    }

    bool groth16_server::serialize_verification_key(
            const r1cs_gg_ppzksnark_verification_key<default_r1cs_gg_ppzksnark_pp>& verification_key,
            const std::string &verification_key_path) {
        std::ofstream proving_key_file(verification_key_path,std::ios::out|std::ios::binary);
        try{
            proving_key_file<<verification_key;
            return true;
        }
        catch (std::exception &e){
            return false;
        }
    }

    bool groth16_server::serialize_proof(const r1cs_gg_ppzksnark_proof<default_r1cs_gg_ppzksnark_pp> &proof,
                                         const std::string &proof_path) {
        std::ofstream proving_key_file(proof_path,std::ios::out|std::ios::binary);
        try{
            proving_key_file<<proof;
            return true;
        }
        catch (std::exception &e){
            return false;
        }
    }

    std::optional<const r1cs_gg_ppzksnark_proving_key<default_r1cs_gg_ppzksnark_pp>>
    groth16_server::get_proving_key_from_file(const std::string &path) {
        try{
            r1cs_gg_ppzksnark_proving_key<default_r1cs_gg_ppzksnark_pp> my_pk ;
            std::ifstream (path)>>my_pk;
            return {my_pk};
        }
        catch (std::exception &e){
            return std::nullopt;
        }
    }

    std::optional<const r1cs_gg_ppzksnark_proof<default_r1cs_gg_ppzksnark_pp>>
    groth16_server::get_proof_from_file(const std::string &path) {
        try{
            r1cs_gg_ppzksnark_proof<default_r1cs_gg_ppzksnark_pp> proof ;
            std::ifstream (path)>>proof;
            return {proof};
        }
        catch (std::exception &e){
            return std::nullopt;
        }
    }

    std::optional<const r1cs_gg_ppzksnark_verification_key<default_r1cs_gg_ppzksnark_pp>>
    groth16_server::get_verification_key_from_file(const std::string &path) {
        try{
            r1cs_gg_ppzksnark_verification_key<default_r1cs_gg_ppzksnark_pp> vk ;
            std::ifstream (path)>>vk;
            return {vk};
        }
        catch (std::exception &e){
            return std::nullopt;
        }
    }

}


#endif
