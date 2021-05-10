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
namespace libserver{
template<typename tinyram_r1cs_params>
const r1cs_primary_input<typename tinyram_r1cs_params::FieldT> r1cs_adapter<tinyram_r1cs_params>::get_r1cs_primary_input(const std::string& primary_input_path) const{
  tinyram_ciruit_ptr_->initial_boot_trace(primary_input_path);
  auto boot_trace = tinyram_ciruit_ptr_->get_boot_trace();
  auto primary_input = compiler_ptr_->compile_r1cs_primary_input(boot_trace).value();
  return primary_input;
}
template<typename tinyram_r1cs_params>
const r1cs_auxiliary_input<typename tinyram_r1cs_params::FieldT> r1cs_adapter<tinyram_r1cs_params>::get_r1cs_auxiliary_input(const std::string& primary_input_path,const std::string& aux_input_path) const{
  tinyram_ciruit_ptr_->initial_boot_trace(primary_input_path);
  tinyram_ciruit_ptr_->initial_aux_input(aux_input_path);
  auto boot_trace = tinyram_ciruit_ptr_->get_boot_trace();
  auto aux_input_tape = tinyram_ciruit_ptr_->get_auxiliary_input_tap();
  auto auxiliary_input = compiler_ptr_->compile_r1cs_auxiliary_input(boot_trace,aux_input_tape).value();
  return auxiliary_input;
}
template<typename tinyram_r1cs_params>
const r1cs_constraint_system<typename tinyram_r1cs_params::FieldT> r1cs_adapter<tinyram_r1cs_params>::get_r1cs_constraint_system()const
{
  return cs_;
}
template<typename tinyram_r1cs_params>
bool r1cs_adapter<tinyram_r1cs_params>::verify(const r1cs_primary_input<typename tinyram_r1cs_params::FieldT>& primary_input,const r1cs_auxiliary_input<typename tinyram_r1cs_params::FieldT>& auxiliary_input) {
  return cs_.is_satisfied(primary_input, auxiliary_input);
}
}
