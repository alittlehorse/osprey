/** @file
 *****************************************************************************

Declaration of interface of r1cs_adapter.
 r1cs_adapter translates three part:
 1. tinyram_circuit to r1cs constraint system
 2. tinyram_primary input to r1cs primary input
 3. tinyram aux_struct input to r1cs aux_struct input

 this interface is like a adapter for tinyram circuit and zk proof system use them.

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/
#ifndef OSPREY_R1CS_ADAPTER_HPP
#define OSPREY_R1CS_ADAPTER_HPP

#include <libserver/proof_systems/tinyram_circuit.hpp>
#include <tinyram_snark/reductions/ram_to_r1cs/ram_to_r1cs.hpp>
#include <tinyram_snark/relations/constraint_satisfaction_problems/r1cs/r1cs.hpp>
#include <libserver/aux_struct/proof_params_config.hpp>
#include <libserver/ram_compiler/tinyram_compiler_server.hpp>
#include <libserver/aux_struct/proof_params_config.hpp>
using tinyram_snark::ram_to_r1cs;
using tinyram_snark::r1cs_constraint_system;
using tinyram_snark::r1cs_primary_input;
using tinyram_snark::r1cs_auxiliary_input;

namespace libserver{
/// \tparam tinyram_r1cs_params
/// r1cs_adapter is adapter to translating tinyram circuit,witness,statement to r1cs format
/// which zk proof system interface used as params
template<typename tinyram_r1cs_params>
class r1cs_adapter {
 public:
  explicit r1cs_adapter(std::unique_ptr<params_config>&& p){
    tinyram_r1cs_params::init_public_params();
    tinyram_ciruit_ = std::unique_ptr<tinyram_circuit<tinyram_r1cs_params>>(new tinyram_circuit<tinyram_r1cs_params>(std::move(p)));
    auto ap = tinyram_ciruit_->get_ram_architecture_params();
    auto bounds = tinyram_ciruit_->get_bounds();

    size_t tinyram_input_size_bound, tinyram_program_size_bound, time_bound;
    tinyram_input_size_bound = bounds["tinyram_input_size_bound"];
    tinyram_program_size_bound = bounds["tinyram_program_size_bound"];
    time_bound = bounds["time_bound"];
    const size_t boot_trace_size_bound = tinyram_input_size_bound + tinyram_program_size_bound;

    auto program = tinyram_ciruit_->get_tinyram_program();
    auto b = tinyram_ciruit_->initial_boot_trace("../../libserver/tutorial/avarage/primary_input.txt");
    auto a = tinyram_ciruit_->initial_aux_input("../../libserver/tutorial/avarage/auxiliary_input.txt");
    auto boot_trace = tinyram_ciruit_->get_boot_trace();

    auto aux_input_tape = tinyram_ciruit_->get_auxiliary_input_tap();
    //primary_input = ram_to_r1cs<typename tinyram_r1cs_params::machine_pp>::primary_input_map(ap, boot_trace_size_bound, boot_trace);
    //auxiliary_input = r.auxiliary_input_map(boot_trace, aux_input_tape);
    //cs = r.get_constraint_system();
    //r.print_execution_trace();
    tinyram_compiler_server<tinyram_r1cs_params> compiler("avarage/avarage-log.txt");
    compiler.specialization(ap,boot_trace_size_bound,time_bound);
    cs = compiler.compile_r1cs_constrain_system().value();
    primary_input = compiler.compile_r1cs_primary_input(boot_trace).value();
    auxiliary_input = compiler.compile_r1cs_auxiliary_input(boot_trace,aux_input_tape).value();

    assert(cs.is_satisfied(primary_input, auxiliary_input)==true);
  }

  const r1cs_primary_input<typename tinyram_r1cs_params::FieldT> get_r1cs_primary_input() const;

  const r1cs_auxiliary_input<typename tinyram_r1cs_params::FieldT> get_auxiliary_input()const;

  const r1cs_constraint_system<typename tinyram_r1cs_params::FieldT> get_r1cs_constraint_system()const;
 private:
  std::unique_ptr<tinyram_circuit<tinyram_r1cs_params>> tinyram_ciruit_;
  //ram_to_r1cs<typename tinyram_r1cs_params::machine_pp> r;
  r1cs_constraint_system<typename tinyram_r1cs_params::FieldT> cs;
  r1cs_primary_input<typename tinyram_r1cs_params::FieldT> primary_input;
  r1cs_auxiliary_input<typename tinyram_r1cs_params::FieldT> auxiliary_input;
};


}

#include <libserver/proof_systems/r1cs_adapter.tcc>

#endif //OSPREY_R1CS_ADAPTER_HPP
