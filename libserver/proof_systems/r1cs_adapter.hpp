/** @file
 *****************************************************************************

Declaration of interface of r1cs_adapter.
 r1cs_adapter translates three part:
 1. tinyram_circuit to r1cs constraint system
 2. tinyram_primary input to r1cs primary input
 3. tinyram aux input to r1cs aux input

 this interface is like a adapter for tinyram circuit and zk proof system use them.

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/
#ifndef OSPREY_R1CS_ADAPTER_HPP
#define OSPREY_R1CS_ADAPTER_HPP

#include <libserver/proof_systems/tinyram_circuit.hpp>
#include<tinyram_snark/reductions/ram_to_r1cs/ram_to_r1cs.hpp>
#include <tinyram_snark/relations/constraint_satisfaction_problems/r1cs/r1cs.hpp>
#include <libserver/aux/proof_params_config.hpp>
using tinyram_snark::ram_to_r1cs;
using tinyram_snark::r1cs_constraint_system;
using tinyram_snark::r1cs_primary_input;
using tinyram_snark::r1cs_auxiliary_input;
namespace libserver{
    template<typename tinyram_r1cs_params>
    class r1cs_adapter {
    private:
        tinyram_circuit<tinyram_r1cs_params>* _tinyram_ciruit;
        //ram_to_r1cs<typename tinyram_r1cs_params::machine_pp> r;
        r1cs_constraint_system<typename tinyram_r1cs_params::FieldT> cs;
        r1cs_primary_input<typename tinyram_r1cs_params::FieldT> primary_input;
        r1cs_auxiliary_input<typename tinyram_r1cs_params::FieldT> auxiliary_input;
        proof_params_config p;

    public:
        explicit r1cs_adapter(const proof_params_config& p):p(p){
            _tinyram_ciruit = new tinyram_circuit<tinyram_r1cs_params>(p.get_processed_assembly_path(),p.get_computation_bounds_path(),p.get_architecture_params_path(),p.get_primary_input_path());
            auto ap = _tinyram_ciruit->get_ram_architecture_params();
            auto bounds = _tinyram_ciruit->get_bounds();
            
            size_t tinyram_input_size_bound, tinyram_program_size_bound, time_bound;
            tinyram_input_size_bound = bounds["tinyram_input_size_bound"];
            tinyram_program_size_bound = bounds["tinyram_program_size_bound"];
            time_bound = bounds["time_bound"];

            auto program = _tinyram_ciruit->get_tinyram_program();
            auto boot_trace = _tinyram_ciruit->get_boot_trace();

            const size_t boot_trace_size_bound = tinyram_input_size_bound + tinyram_program_size_bound;

            //typedef default_tinyram_gg_ppzksnark_pp::machine_pp default_ram_with_Fr;
            //
            ram_to_r1cs<typename tinyram_r1cs_params::machine_pp> r(ap, boot_trace_size_bound, time_bound);
            r.instance_map();
            std::ifstream f_auxiliary_input(p.get_auxiliary_input_path());

            libff::enter_block("Loading auxiliary input");
            tinyram_snark::tinyram_input_tape aux_input = tinyram_snark::load_tape(f_auxiliary_input);
            libff::leave_block("Loading auxiliary input");


            primary_input = ram_to_r1cs<typename tinyram_r1cs_params::machine_pp>::primary_input_map(ap, boot_trace_size_bound, boot_trace);
            auxiliary_input = r.auxiliary_input_map(boot_trace, aux_input);
            cs = r.get_constraint_system();

            //r.print_execution_trace();
            assert(cs.is_satisfied(primary_input, auxiliary_input)==true);
        }

        const r1cs_primary_input<typename tinyram_r1cs_params::FieldT> get_r1cs_primary_input();

        const r1cs_auxiliary_input<typename tinyram_r1cs_params::FieldT> get_auxiliary_input();

        const r1cs_constraint_system<typename tinyram_r1cs_params::FieldT> get_r1cs_constraint_system();
    };


}

#include <libserver/proof_systems/r1cs_adapter.tcc>

#endif //OSPREY_R1CS_ADAPTER_HPP
