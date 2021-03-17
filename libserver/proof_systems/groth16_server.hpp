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
#include <libserver/proof_systems/proof_public_params.hpp>

#include <libserver/ram_complier/tinyram_complier_server.hpp>
#include <libserver/aux/proof_program.hpp>
#include <libserver/aux/Log.hpp>
#include <unordered_map>

using namespace tinyram_snark;
namespace  libserver{
    class groth16_server {
    public:
        groth16_server(const proof_program& vp):_vp(vp),
        _proof_public_params(proof_public_params<default_r1cs_gg_ppzksnark_pp>("avarage/avarage-processed_assembly.txt",
                                                                               "avarage/avarage-computation_bounds.txt",
                                                                               "avarage/avarage-architecture_params.txt",
                                                                               "avarage/avarage-primary_input.txt"))
        {

        }
        bool construct_proof();

        std::optional<r1cs_gg_ppzksnark_proof<default_r1cs_gg_ppzksnark_pp>> generate_proof();

        bool construct_proof1();

    private:
        proof_program _vp;
        Log* log;
        proof_public_params<default_r1cs_gg_ppzksnark_pp> _proof_public_params;
        r1cs_constraint_system<libff::Fr<default_r1cs_gg_ppzksnark_pp>> constraint_system;
        r1cs_constraint_system<libff::Fr<default_r1cs_gg_ppzksnark_pp>> generate_r1cs();
    };
}


#include <libserver/proof_systems/groth16_server.tcc>


#endif //OSPREY_GROTH16_SERVER_HPP


