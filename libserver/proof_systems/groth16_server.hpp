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



#ifndef OSPREY_GROTH16_SERVER_HPP
#define OSPREY_GROTH16_SERVER_HPP

#include <tinyram_snark/common/default_types/tinyram_gg_ppzksnark_pp.hpp>
#include <tinyram_snark/reductions/ram_to_r1cs/ram_to_r1cs.hpp>
#include <tinyram_snark/relations/ram_computations/rams/tinyram/tinyram_params.hpp>
#include <tinyram_snark/zk_proof_systems/r1cs_gg_ppzksnark/r1cs_gg_ppzksnark.hpp>
#include <libserver/proof_systems/tinyram_circuit.hpp>
#include <libserver/aux/Log.hpp>

#include <depends/fmt/include/fmt/ostream.h>
#include <libserver/aux/proof_params_config.hpp>
#include <libserver/aux/Log.hpp>
#include <unordered_map>
#include <libserver/proof_systems/r1cs_adapter.hpp>
#include <iostream>

using namespace tinyram_snark;
namespace  libserver{
    class groth16_server {
    private:
        typedef tinyram_r1cs_pp<default_r1cs_gg_ppzksnark_pp> tinyram_r1cs_params;
        std::string initial_path;
        r1cs_adapter<tinyram_r1cs_params>* _r1cs_adapter;
        r1cs_gg_ppzksnark_proving_key<default_r1cs_gg_ppzksnark_pp> pk;
        Log* log;
        proof_params_config _vp;

    public:
        explicit groth16_server(const std::string& initial_path):initial_path(initial_path){
            _vp = *new proof_params_config(std::move(initial_path));
            _r1cs_adapter = new r1cs_adapter<tinyram_r1cs_params>(_vp);
            log = new Log((_vp.get_log_path()));
        };
        bool construct_proof1();

    };
}


#include <libserver/proof_systems/groth16_server.tcc>


#endif //OSPREY_GROTH16_SERVER_HPP


