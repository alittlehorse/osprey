/** @file
 *****************************************************************************

the server of zksnark using the proof program with tinyram
 + generate_proof
 + test_proof
 + generate keypair
 + generate architecture params
 + get bounds(time bounds, compution bounds...)

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/

#ifndef OSPREY_CONSTRUCT_PROOF_H
#define OSPREY_CONSTRUCT_PROOF_H



#include <tinyram_snark/common/default_types/tinyram_ppzksnark_pp.hpp>
#include <tinyram_snark/reductions/ram_to_r1cs/ram_to_r1cs.hpp>
#include <tinyram_snark/relations/ram_computations/rams/tinyram/tinyram_params.hpp>
#include <tinyram_snark/zk_proof_systems/ppzksnark/ram_ppzksnark/ram_ppzksnark.hpp>
#include <libserver/proof_program.hpp>
#include <libserver/Log.hpp>
#include <libff/common/profiling.hpp>
#include <iostream>
#include <string>

using namespace tinyram_snark;

namespace libserver{

    using proof = tinyram_snark::ram_ppzksnark_proof<default_tinyram_ppzksnark_pp>;
    using boot_trace = ram_boot_trace<default_tinyram_ppzksnark_pp>;
    using ram_keypair = ram_ppzksnark_keypair<default_tinyram_ppzksnark_pp> ;
    using architecture_params = ram_ppzksnark_architecture_params<default_tinyram_ppzksnark_pp>;

    class ram_ppsnark_server{
    public :
        typedef libff::Fr<libff::default_ec_pp> FieldT;
        explicit ram_ppsnark_server(proof_program&);
        std::string get_target_path();


        ///genreta_proof use the keypair ,primary_input and axuliriay_input to generate a proof which can pass the verifing
        /// with the giving keypair. this function should called by the server provider.
        /// input param: keypair ,primary_input and axuliriay_input,
        /// \return proof
        proof generate_proof(const ram_keypair&,const boot_trace&,tinyram_input_tape&) const;

        /// this function use the tinyrma program path to generate the ppsnark architecture params
        /// this function should called by the trust third part;

        architecture_params genenerate_ram_ppsnark_architecture_params();
        /// this function use the tinyrma program architecure_params path to generate the ppsnark architecture params
        /// this function should called by the trust third part;
        /// \return proof
        architecture_params generate_ram_ppsnark_architecture_params(std::string&&);
        ///generate_ram_ppsnark_keypair function Logs the processing of Key Pair Genetator and using tinyram_snark::ram_ppzksnark_generator to construct a keypair;
        ///this function should called by the trust third part;
        /// \param ap : the atchitecute_params of tinyram
        /// \param boot_trace_size_bound:primary input size bound
        /// \param time_bound: the program execution time bound
        /// \return ram_keypair;
        ram_keypair generate_ram_ppsnark_keypair(const architecture_params& ,size_t,size_t);
        /// verify the proof whethear it can pass;
        bool test_proof(const proof& ,const boot_trace& ,const ram_keypair& );

        ///generate the primary inpute using the architecture_params and boot_trace_size_bound;
        boot_trace generate_primary_input(const architecture_params &ap, size_t boot_trace_size_bound);

        tinyram_input_tape generate_auxili_input();
        /// generate the auxili_input using the program auxili input path; this
        ///this function should called by server provider;
        tinyram_input_tape generate_auxili_input(std::string&&);
        /// generate:
        /// tinyram_input_size_bound
        /// tinyram_program_size_bound
        /// time_bound
        /// return :\tuple<tinyram_input_size_bound,tinyram_program_size_bound,time_bound>
        std::tuple<size_t,size_t,size_t> get_bounds();
        ///reduce ram to r1cs
        r1cs_constraint_system<FieldT> ram2r1cs();

    private:
        proof_program _vp;
        Log* log;
        // just a test function ,
        //proof construct_proof();
    };
}

#endif //OSPREY_CONSTRUCT_PROOF_H