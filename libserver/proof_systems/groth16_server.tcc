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



#include <libserver/Log.hpp>
#include <tuple>
#include <tinyram_snark/common/default_types/tinyram_gg_ppzksnark_pp.hpp>
#include <tinyram_snark/reductions/ram_to_r1cs/ram_to_r1cs.hpp>
#include <tinyram_snark/relations/ram_computations/rams/tinyram/tinyram_params.hpp>
#include <tinyram_snark/zk_proof_systems/r1cs_gg_ppzksnark/r1cs_gg_ppzksnark.hpp>

using namespace tinyram_snark;
namespace  libserver{
        bool groth16_server::construct_proof(){
            //reduce from ram to r1cs
            // product prover key and verifier key

            typedef ram_tinyram<default_r1cs_gg_ppzksnark_pp> default_ram_with_pp;

            default_r1cs_gg_ppzksnark_pp::init_public_params();


            log->write_log<>("================================================================================\n");
            log->write_log<>("TinyRAM example loader\n");
            log->write_log<>("================================================================================\n\n");

            /* load everything */
            ram_architecture_params<default_ram_with_pp> ap;
            std::ifstream f_ap(_vp.get_architecture_params_fn());
            f_ap >> ap;

            log->write_log<size_t,size_t>("Will run on %zu register machine (word size = %zu)\n", ap.k, ap.w);

            std::ifstream f_rp(_vp.get_computation_bounds_fn());
            size_t tinyram_input_size_bound, tinyram_program_size_bound, time_bound;
            f_rp >> tinyram_input_size_bound >> tinyram_program_size_bound >> time_bound;

            std::ifstream processed(_vp.get_processed_assembly_fn());
            tinyram_program program = load_preprocessed_program(ap, processed);

            std::ifstream f_primary_input(_vp.get_primary_input_fn());
            std::ifstream f_auxiliary_input(_vp.get_auxiliary_input_fn());

            libff::enter_block("Loading primary input");
            tinyram_input_tape primary_input(load_tape(f_primary_input));
            libff::leave_block("Loading primary input");

            libff::enter_block("Loading auxiliary input");
            tinyram_input_tape auxiliary_input = load_tape(f_auxiliary_input);
            libff::leave_block("Loading auxiliary input");

            const size_t boot_trace_size_bound = tinyram_input_size_bound + tinyram_program_size_bound;
            const ram_boot_trace<default_ram_with_pp> boot_trace = tinyram_boot_trace_from_program_and_input(ap, boot_trace_size_bound, program, primary_input);

            typedef default_tinyram_gg_ppzksnark_pp::machine_pp default_ram_with_Fr;

            ram_to_r1cs<default_ram_with_Fr> r(ap, boot_trace_size_bound, time_bound);
            r.instance_map();

            //already in Fr,change to point at ppT
            const r1cs_primary_input<default_ram_with_Fr::base_field_type> r1cs_primary_input = ram_to_r1cs<default_ram_with_Fr>::primary_input_map(ap, boot_trace_size_bound, boot_trace);
            const r1cs_auxiliary_input<default_ram_with_Fr::base_field_type> r1cs_auxiliary_input = r.auxiliary_input_map(boot_trace, auxiliary_input);
            const r1cs_constraint_system<default_ram_with_Fr::base_field_type> constraint_system = r.get_constraint_system();

            //r.print_execution_trace();

            const bool bit = constraint_system.is_satisfied(r1cs_primary_input, r1cs_auxiliary_input);

            log->write_log<>("================================================================================\n");
            log->write_log<std::string>("The verification result is: %s\n", (bit ? "PASS" : "FAIL"));
            log->write_log<>("================================================================================\n");

            //typedef libff::Fr<libff::default_ec_pp> FieldT;
            //typedef ram_tinyram<FieldT> default_ram;

            auto keypair = r1cs_gg_ppzksnark_generator<default_r1cs_gg_ppzksnark_pp>(constraint_system);//OK!


            const r1cs_gg_ppzksnark_proof<default_r1cs_gg_ppzksnark_pp> proof = r1cs_gg_ppzksnark_prover<default_r1cs_gg_ppzksnark_pp>(keypair.pk,r1cs_primary_input,r1cs_auxiliary_input);
            bool b = r1cs_gg_ppzksnark_verifier_strong_IC<default_r1cs_gg_ppzksnark_pp>(keypair.vk, r1cs_primary_input, proof);
            assert(b== true);
            log->write_log<>("================================================================================\n");
            log->write_log<>("The verification result is: %s\n", (b ? "PASS" : "FAIL"));
            log->write_log<>("================================================================================\n");
            return b;
        }

        template<typename ramT>
        std::optional<const ram_architecture_params<ramT>> groth16_server::generate_ram_architecture_params(std::string&& architecture_params_file_path){
            //ram_architecture_params<default_ram_with_pp> ap;
            ram_architecture_params<ramT> ap;
            try{
                std::ifstream f_ap(architecture_params_file_path);
                f_ap >> ap;
            }
            catch(exception &e){
                return nullopt;
            }
            return {ap};
        }

        std::optional<const std::tuple<size_t,size_t,size_t>> groth16_server::get_bounds(std::string&& bounds_filepath){
            size_t tinyram_input_size_bound, tinyram_program_size_bound, time_bound;
            try{
                std::ifstream f_rp(bounds_filepath);
                f_rp >> tinyram_input_size_bound >> tinyram_program_size_bound >> time_bound;
            }
            catch(exception &e){
                return nullopt;
            }
            return {std::make_tuple(tinyram_input_size_bound,tinyram_program_size_bound,time_bound)};
        }
        std::optional<tinyram_program> groth16_server::generate_program(std::string&& processed_assemble_filepath,const tinyram_architecture_params& ap){
            tinyram_program program;
            try{
                std::ifstream processed(processed_assemble_filepath);
                program = load_preprocessed_program(ap, processed);
            }
            catch (exception &e){
                return nullopt;
            }

            return {program};
        }


}



