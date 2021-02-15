/** @file
 *****************************************************************************

 Declaration of interfaces for a verfication program provided by server requester

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <libff/common/profiling.hpp>

#include <tinyram_snark/common/default_types/tinyram_ppzksnark_pp.hpp>
#include <tinyram_snark/reductions/ram_to_r1cs/ram_to_r1cs.hpp>
#include <tinyram_snark/relations/ram_computations/rams/tinyram/tinyram_params.hpp>

#include <libserver/ram_ppsnark_server.hpp>
#include <libserver/Log.hpp>
#include <libserver/proof_program.hpp>

using namespace tinyram_snark;

namespace libserver{
     ram_ppsnark_server::ram_ppsnark_server(proof_program& v) {
         _vp = v;
         log = new Log(v.get_program_name()+"/"+v.get_program_name()+"_log.txt");
         default_tinyram_ppzksnark_pp::init_public_params();
         libff::start_profiling();
    }
    proof ram_ppsnark_server::construct_proof() {

        log->write_log<>("================================================================================\n");
        log->write_log<>("TinyRAM example loader\n");
        log->write_log<>("================================================================================\n\n");

        //load everything
        auto ap = generate_ram_ppsnark_architecture_params(_vp.get_architecture_params_fn());
        log->write_log<size_t,size_t>("Will run on %zu register machine (word size = %zu)\\n", ap.k, ap.w);

        std::ifstream f_rp(_vp.get_computation_bounds_fn());
        size_t tinyram_input_size_bound, tinyram_program_size_bound, time_bound;
        f_rp >> tinyram_input_size_bound >> tinyram_program_size_bound >> time_bound;
        const size_t boot_trace_size_bound = tinyram_program_size_bound + tinyram_input_size_bound;

        const boot_trace primary_input_boot_trace = generate_primary_input(ap,boot_trace_size_bound);
        auto auxiliary_input = generate_auxili_input(_vp.get_auxiliary_input_fn());

        log->write_log<>("================================================================================\n");
        log->write_log<size_t>("TinyRAM arithmetization test for T = %zu time steps\n", time_bound);
        log->write_log<>("================================================================================\n\n");

        typedef ram_ppzksnark_machine_pp<default_tinyram_ppzksnark_pp> default_ram;
        typedef ram_base_field<default_ram> FieldT;

        ram_to_r1cs<default_ram> r(ap, boot_trace_size_bound, time_bound);
        r.instance_map();

        const r1cs_primary_input<FieldT> r1cs_primary_input = ram_to_r1cs<default_ram>::primary_input_map(ap, boot_trace_size_bound, primary_input_boot_trace);
        const r1cs_auxiliary_input<FieldT> r1cs_auxiliary_input = r.auxiliary_input_map(primary_input_boot_trace, auxiliary_input);
        const r1cs_constraint_system<FieldT> constraint_system = r.get_constraint_system();

//        r.print_execution_trace(proof_log->get_path()); //rediract to log
        assert(constraint_system.is_satisfied(r1cs_primary_input, r1cs_auxiliary_input));

        auto keypair = generate_ram_ppsnark_keypair(ap, boot_trace_size_bound, time_bound);
        auto proof = construct_proof(keypair,primary_input_boot_trace,auxiliary_input);

        assert(ram_ppzksnark_verifier<default_tinyram_ppzksnark_pp>(keypair.vk, primary_input_boot_trace, proof)==true);
        libff::print_mem();
        return proof;
    }

    proof ram_ppsnark_server::construct_proof(const ram_keypair& keypair,const boot_trace& bt,tinyram_input_tape& auxiliary_input) const{
        log->write_log<>("================================================================================\n");
        log->write_log<>("TinyRAM ppzkSNARK Prover\n");
        log->write_log<>("================================================================================\n\n");
        const proof p = ram_ppzksnark_prover<default_tinyram_ppzksnark_pp>(keypair.pk, bt,  auxiliary_input);
        assert(ram_ppzksnark_verifier<default_tinyram_ppzksnark_pp>(keypair.vk, bt, p)==true);
        libff::print_mem();
        return p;
     }


    ram_keypair ram_ppsnark_server::generate_ram_ppsnark_keypair(const architecture_params& ap,size_t boot_trace_size_bound,size_t time_bound) {
        log->write_log<>("================================================================================\n");
        log->write_log<>("TinyRAM ppzkSNARK Key Pair Generator\n");
        log->write_log<>("================================================================================\n\n");

        const ram_keypair keypair = ram_ppzksnark_generator<default_tinyram_ppzksnark_pp>(ap, boot_trace_size_bound, time_bound);
        return keypair;
    }

    architecture_params
    ram_ppsnark_server::generate_ram_ppsnark_architecture_params(std::string&& get_architecture_params_fn) {
        architecture_params ap;
        std::ifstream f_ap(get_architecture_params_fn);
        f_ap >> ap;
        return ap;
    }

    boot_trace ram_ppsnark_server::generate_primary_input(const architecture_params& ap,const size_t boot_trace_size_bound){

        std::ifstream processed(_vp.get_processed_assembly_fn());
        std::ifstream raw(_vp.get_assembly_fn());
        tinyram_program program = load_preprocessed_program(ap, processed);

        log->write_log<std::string>("Program:\n%s\n", std::string((std::istreambuf_iterator<char>(raw)),
                                                                  std::istreambuf_iterator<char>()).c_str());
        std::ifstream f_primary_input(_vp.get_primary_input_fn());
        libff::enter_block("Loading primary input");
        tinyram_input_tape primary_input = load_tape(f_primary_input);
        libff::leave_block("Loading primary input");

        const boot_trace primary_input_boot_trace = tinyram_boot_trace_from_program_and_input(ap, boot_trace_size_bound, program, primary_input);
        return primary_input_boot_trace;
     }
    tinyram_input_tape ram_ppsnark_server::generate_auxili_input(std::string&& auxiliary_input_path){
         std::ifstream f_auxiliary_input(auxiliary_input_path);
         libff::enter_block("Loading auxiliary input");
         tinyram_input_tape auxiliary_input = load_tape(f_auxiliary_input);
         libff::leave_block("Loading auxiliary input");
         return auxiliary_input;
     }

     bool ram_ppsnark_server::test_proof(const proof& p,
                                        const boot_trace& bt,
                                        const ram_keypair& keypair){
         libff::start_profiling();
         bool bit = ram_ppzksnark_verifier<default_tinyram_ppzksnark_pp>(keypair.vk, bt, p);
         return bit;
    }

    std::string ram_ppsnark_server::get_target_path() {
        return _vp.get_program_name();
    }


}