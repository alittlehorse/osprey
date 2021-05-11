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

#include <libserver/ram_compiler/tinyram_compiler_server.hpp>

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
    tinyram_ciruit_ptr_ = std::make_unique<tinyram_circuit<tinyram_r1cs_params>>(std::move(p));
    auto ap = tinyram_ciruit_ptr_->get_ram_architecture_params();
    auto bounds = tinyram_ciruit_ptr_->get_bounds();

    size_t tinyram_input_size_bound, tinyram_program_size_bound, time_bound;
    tinyram_input_size_bound = bounds["tinyram_input_size_bound"];
    tinyram_program_size_bound = bounds["tinyram_program_size_bound"];
    time_bound = bounds["time_bound"];
    const size_t boot_trace_size_bound = tinyram_input_size_bound + tinyram_program_size_bound;

    auto program = tinyram_ciruit_ptr_->get_tinyram_program();

    //r.print_execution_trace();
    compiler_ptr_ = std::make_unique<tinyram_compiler_server<tinyram_r1cs_params>>("avarage/avarage-log.txt");
    compiler_ptr_->specialization(ap,boot_trace_size_bound,time_bound);
    cs_ = compiler_ptr_->compile_r1cs_constrain_system().value();
  }

  const r1cs_primary_input<typename tinyram_r1cs_params::FieldT> get_r1cs_primary_input(const std::string& primary_input_path) const;

  const r1cs_auxiliary_input<typename tinyram_r1cs_params::FieldT> get_r1cs_auxiliary_input(const std::string& primary_input_path,const std::string& aux_input_path)const;

  const r1cs_constraint_system<typename tinyram_r1cs_params::FieldT> get_r1cs_constraint_system()const;

  bool verify(const r1cs_primary_input<typename tinyram_r1cs_params::FieldT> &primary_input, const r1cs_auxiliary_input<typename tinyram_r1cs_params::FieldT> &auxiliary_input);
 private:
  std::unique_ptr<tinyram_circuit<tinyram_r1cs_params>> tinyram_ciruit_ptr_;
  r1cs_constraint_system<typename tinyram_r1cs_params::FieldT> cs_;
  std::unique_ptr<tinyram_compiler_server<tinyram_r1cs_params>> compiler_ptr_ = nullptr;
};
}

#include <libserver/proof_systems/r1cs_adapter.tcc>

#endif //OSPREY_R1CS_ADAPTER_HPP
