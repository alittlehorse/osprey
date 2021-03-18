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
    bool groth16_server::construct_proof(){
            log = new Log(_vp->get_program_name()+"/"+_vp->get_program_name()+"-log.txt");
            //reduce from ram to r1cs
            // product prover key and verifier key
            default_tinyram_gg_ppzksnark_pp::init_public_params();

            //typedef ram_tinyram<default_r1cs_gg_ppzksnark_pp> default_ram_with_pp;

            log->write_log<>("================================================================================\n");
            log->write_log<>("TinyRAM example loader\n");
            log->write_log<>("================================================================================\n\n");

            /* load everything */
            ram_architecture_params<default_tinyram_gg_ppzksnark_pp::machine_pp> ap;
            std::ifstream f_ap(_vp->get_architecture_params_fn());
            f_ap >> ap;

            log->write_log<size_t,size_t>("Will run on %zu register machine (word size = %zu)\n", ap.k, ap.w);

            std::ifstream f_rp(_vp->get_computation_bounds_fn());
            size_t tinyram_input_size_bound, tinyram_program_size_bound, time_bound;
            f_rp >> tinyram_input_size_bound >> tinyram_program_size_bound >> time_bound;

            std::ifstream processed(_vp->get_processed_assembly_fn());
            tinyram_program program = load_preprocessed_program(ap, processed);

            std::ifstream f_primary_input(_vp->get_primary_input_fn());
            std::ifstream f_auxiliary_input(_vp->get_auxiliary_input_fn());

            libff::enter_block("Loading primary input");
            tinyram_input_tape primary_input(load_tape(f_primary_input));
            libff::leave_block("Loading primary input");

            libff::enter_block("Loading auxiliary input");
            tinyram_input_tape auxiliary_input = load_tape(f_auxiliary_input);
            libff::leave_block("Loading auxiliary input");

            const size_t boot_trace_size_bound = tinyram_input_size_bound + tinyram_program_size_bound;
            const ram_boot_trace<default_tinyram_gg_ppzksnark_pp::machine_pp> boot_trace = tinyram_boot_trace_from_program_and_input(ap, boot_trace_size_bound, program, primary_input);

            //typedef default_tinyram_gg_ppzksnark_pp::machine_pp default_ram_with_Fr;

            ram_to_r1cs<default_tinyram_gg_ppzksnark_pp::machine_pp> r(ap, boot_trace_size_bound, time_bound);
            r.instance_map();

            //already in Fr,change to point at ppT
            const r1cs_primary_input<default_tinyram_gg_ppzksnark_pp::machine_pp::base_field_type> r1cs_primary_input = ram_to_r1cs<default_tinyram_gg_ppzksnark_pp::machine_pp>::primary_input_map(ap, boot_trace_size_bound, boot_trace);
            const r1cs_auxiliary_input<default_tinyram_gg_ppzksnark_pp::machine_pp::base_field_type> r1cs_auxiliary_input = r.auxiliary_input_map(boot_trace, auxiliary_input);
            const r1cs_constraint_system<default_tinyram_gg_ppzksnark_pp::machine_pp::base_field_type> constraint_system = r.get_constraint_system();

            //r.print_execution_trace();

            const bool bit = constraint_system.is_satisfied(r1cs_primary_input, r1cs_auxiliary_input);

            log->write_log<>("================================================================================\n");
            log->write_log<std::string>("The verification result is: %s\n", (bit ? "PASS" : "FAIL"));
            log->write_log<>("================================================================================\n");

            //typedef libff::Fr<libff::default_ec_pp> FieldT;
            //typedef ram_tinyram<FieldT> default_ram;

            auto keypair = r1cs_gg_ppzksnark_generator<default_tinyram_gg_ppzksnark_pp::snark_pp>(constraint_system);//OK!


            const r1cs_gg_ppzksnark_proof<default_tinyram_gg_ppzksnark_pp::snark_pp> proof = r1cs_gg_ppzksnark_prover<default_tinyram_gg_ppzksnark_pp::snark_pp>(keypair.pk,r1cs_primary_input,r1cs_auxiliary_input);
            bool b = r1cs_gg_ppzksnark_verifier_strong_IC<default_tinyram_gg_ppzksnark_pp::snark_pp>(keypair.vk, r1cs_primary_input, proof);
            assert(b== true);
            log->write_log<>("================================================================================\n");
            log->write_log<>("The verification result is: %s\n", (b ? "PASS" : "FAIL"));
            log->write_log<>("================================================================================\n");
            return b;
        }

    bool groth16_server::construct_proof1() {
        log = new Log(_vp->get_program_name()+"/"+_vp->get_program_name()+"-log.txt");
        auto keypair = r1cs_gg_ppzksnark_generator<tinyram_r1cs_params::snark_pp>(_r1cs_adapter->get_r1cs_constraint_system());//OK!

        const r1cs_gg_ppzksnark_proof<tinyram_r1cs_params::snark_pp> proof = r1cs_gg_ppzksnark_prover<tinyram_r1cs_params::snark_pp>(keypair.pk,_r1cs_adapter->get_r1cs_primary_input(),_r1cs_adapter->get_auxiliary_input());
        bool b = r1cs_gg_ppzksnark_verifier_strong_IC<tinyram_r1cs_params::snark_pp>(keypair.vk, _r1cs_adapter->get_r1cs_primary_input(), proof);
        assert(b== true);
        log->write_log<>("================================================================================\n");
        log->write_log<>("The verification result is: %s\n", (b ? "PASS" : "FAIL"));
        log->write_log<>("================================================================================\n");
        return b;
    }

}



