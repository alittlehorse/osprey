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
#pragma once
#ifndef OSPREY_GROTH16_SERVER_HPP_
#define OSPREY_GROTH16_SERVER_HPP_


#include <tinyram_snark/common/default_types/tinyram_gg_ppzksnark_pp.hpp>
#include <tinyram_snark/reductions/ram_to_r1cs/ram_to_r1cs.hpp>
#include <tinyram_snark/relations/ram_computations/rams/tinyram/tinyram_params.hpp>
#include <tinyram_snark/zk_proof_systems/r1cs_gg_ppzksnark/r1cs_gg_ppzksnark.hpp>
#include <libserver/proof_systems/tinyram_circuit.hpp>
#include <libserver/aux_struct/Log.hpp>
#include <libserver/aux_struct/proof_params_config.hpp>
#include <libserver/aux_struct/Log.hpp>

#include <depends/fmt/include/fmt/ostream.h>

#include <libserver/proof_systems/r1cs_adapter.hpp>
#include <iostream>
#include <optional>
#include <unordered_map>

using namespace tinyram_snark;
namespace  libserver{
    class groth16_server {
    private:
        typedef tinyram_r1cs_pp<default_r1cs_gg_ppzksnark_pp> tinyram_r1cs_params;
        r1cs_adapter<tinyram_r1cs_params>* _r1cs_adapter;
        Log* log;
        proof_params_config _vp;

    public:
        explicit groth16_server(proof_params_config  vp):_vp(std::move(vp)){
            _r1cs_adapter = new r1cs_adapter<tinyram_r1cs_params>(_vp);
            log = new Log((_vp.get_log_path()));
        };

        std::optional<const r1cs_gg_ppzksnark_proof<default_r1cs_gg_ppzksnark_pp>>
        generate_proof(const r1cs_gg_ppzksnark_proving_key<default_r1cs_gg_ppzksnark_pp>& proving_key);

        std::optional<const r1cs_gg_ppzksnark_keypair<default_r1cs_gg_ppzksnark_pp>>
        generate_keypair();

        bool verify(const r1cs_gg_ppzksnark_verification_key<default_r1cs_gg_ppzksnark_pp>& verification_key,
                                    const r1cs_gg_ppzksnark_proof<default_r1cs_gg_ppzksnark_pp>& proof);

        static bool serialize_proveing_key(const r1cs_gg_ppzksnark_proving_key<default_r1cs_gg_ppzksnark_pp>& proving_key,
                                                    const std::string& proving_key_path);
        static bool serialize_verification_key(const r1cs_gg_ppzksnark_verification_key<default_r1cs_gg_ppzksnark_pp>& verification_key,
                                        const std::string& verification_key_path);
        static bool serialize_proof(const r1cs_gg_ppzksnark_proof<default_r1cs_gg_ppzksnark_pp>& proof,
                             const std::string& proof_path);
        static std::optional<const r1cs_gg_ppzksnark_proving_key<default_r1cs_gg_ppzksnark_pp>>
        get_proving_key_from_file(const std::string &path);

        static std::optional<const r1cs_gg_ppzksnark_verification_key<default_r1cs_gg_ppzksnark_pp>>
        get_verification_key_from_file(const std::string& path);

        static std::optional<const r1cs_gg_ppzksnark_proof<default_r1cs_gg_ppzksnark_pp>>
        get_proof_from_file(const std::string &path);
    };
}

#include <libserver/proof_systems/groth16_server.tcc>

#endif //OSPREY_GROTH16_SERVER_HPP_


