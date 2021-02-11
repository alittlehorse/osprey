/** @file
 *****************************************************************************

 Declaration of interfaces for a verfication program provided by server requester

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/

#ifndef OSPREY_CONSTRUCT_PROOF_H
#define OSPREY_CONSTRUCT_PROOF_H

#endif //OSPREY_CONSTRUCT_PROOF_H

#include <tinyram_snark/common/default_types/tinyram_ppzksnark_pp.hpp>
#include <tinyram_snark/reductions/ram_to_r1cs/ram_to_r1cs.hpp>
#include <tinyram_snark/relations/ram_computations/rams/tinyram/tinyram_params.hpp>
#include <tinyram_snark/zk_proof_systems/ppzksnark/ram_ppzksnark/ram_ppzksnark.hpp>
#include <libserver/proof_program.hpp>
#include <libserver/Log.hpp>

using namespace tinyram_snark;

namespace libserver{
    using proof = tinyram_snark::ram_ppzksnark_proof<default_tinyram_ppzksnark_pp>;
    using boot_trace = ram_boot_trace<default_tinyram_ppzksnark_pp>;
    using ram_keypair = ram_ppzksnark_keypair<default_tinyram_ppzksnark_pp> ;
    class ram_ppsnark_server{
    public :
        explicit ram_ppsnark_server(proof_program&);
        proof construct_proof();
        ram_ppzksnark_architecture_params<default_tinyram_ppzksnark_pp> generate_ram_ppsnark_architecture_params(std::string&&);
        ram_keypair generate_ram_ppsnark_keypair(ram_ppzksnark_architecture_params<default_tinyram_ppzksnark_pp> ,size_t,size_t);
        static bool test_proof(const proof& ,const boot_trace& ,const ram_keypair& );

    private:
        proof_program _vp;
        Log* log;
    };


}

