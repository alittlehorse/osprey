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
    using architecture_params = ram_ppzksnark_architecture_params<default_tinyram_ppzksnark_pp>;

    class ram_ppsnark_server{
    public :
        explicit ram_ppsnark_server(proof_program&);
        std::string get_target_path();
        proof construct_proof();
        proof construct_proof(const ram_keypair&,const boot_trace&,tinyram_input_tape&) const;
        architecture_params generate_ram_ppsnark_architecture_params(std::string&&);
        ///generate_ram_ppsnark_keypair function Logs the processing of Key Pair Genetator and using tinyram_snark::ram_ppzksnark_generator to construct a keypair;
        /// \param ap : the atchitecute_params of tinyram
        /// \param boot_trace_size_bound:primary input size bound
        /// \param time_bound: the program execution time bound
        /// \return ram_keypair;
        ram_keypair generate_ram_ppsnark_keypair(const architecture_params& ,size_t,size_t);
        bool test_proof(const proof& ,const boot_trace& ,const ram_keypair& );
        boot_trace generate_primary_input(const architecture_params &ap, size_t boot_trace_size_bound);
        tinyram_input_tape generate_auxili_input(std::string&&);
    private:
        proof_program _vp;
        Log* log;
    };
}

