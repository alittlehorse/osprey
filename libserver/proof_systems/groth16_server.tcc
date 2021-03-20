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



#include <libserver/aux/Log.hpp>
#include <tuple>
#include <tinyram_snark/common/default_types/tinyram_gg_ppzksnark_pp.hpp>
#include <tinyram_snark/reductions/ram_to_r1cs/ram_to_r1cs.hpp>
#include <tinyram_snark/relations/ram_computations/rams/tinyram/tinyram_params.hpp>
#include <tinyram_snark/zk_proof_systems/r1cs_gg_ppzksnark/r1cs_gg_ppzksnark.hpp>
#include <libserver/aux/Log.hpp>
#include "groth16_server.hpp"


using namespace tinyram_snark;
namespace  libserver{

    bool groth16_server::construct_proof1() {
        auto keypair = r1cs_gg_ppzksnark_generator<tinyram_r1cs_params::snark_pp>(_r1cs_adapter->get_r1cs_constraint_system());//OK!

        const r1cs_gg_ppzksnark_proof<tinyram_r1cs_params::snark_pp> proof = r1cs_gg_ppzksnark_prover<tinyram_r1cs_params::snark_pp>(keypair.pk,_r1cs_adapter->get_r1cs_primary_input(),_r1cs_adapter->get_auxiliary_input());
        bool b = r1cs_gg_ppzksnark_verifier_strong_IC<tinyram_r1cs_params::snark_pp>(keypair.vk, _r1cs_adapter->get_r1cs_primary_input(), proof);
        assert(b== true);
        log->write_log(fmt::format("verify:{}", b ? "PASS" : "FAIL"));
        return b;
    }

}



