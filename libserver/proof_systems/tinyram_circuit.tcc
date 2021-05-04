/** @file
 *****************************************************************************

Declaration of interface of tinyram_circuit.
 include:
 1. tinyram_program
 2. ram_boot_trace(similar to primary_input),which is embedding primary_input_tape into boot_trace(memory circuit)
 3. ram_architecture_params
 4. bounds
 5. auxiliary_input_tape


 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/
#include <string>
#include <istream>
#include <fstream>
#include <optional>


namespace libserver{
template<typename tinyram_r1cs_params>
const std::unordered_map<const char*,size_t>&
tinyram_circuit<tinyram_r1cs_params>::get_bounds(){
  return this->bounds;
}
template<typename tinyram_r1cs_params>
const tinyram_snark::tinyram_program&
tinyram_circuit<tinyram_r1cs_params>::get_tinyram_program(){
  return this->program;
}
template<typename tinyram_r1cs_params>
const tinyram_snark::ram_boot_trace<typename tinyram_r1cs_params::machine_pp>&
tinyram_circuit<tinyram_r1cs_params>::get_boot_trace(){
  return boot_trace;
}
/*
* the client must call this function after ensuring that 'initial_aux_input' has been called
*/
template<typename tinyram_r1cs_params>
const tinyram_snark::tinyram_input_tape &tinyram_circuit<tinyram_r1cs_params>::get_auxiliary_input_tap() {
  return auxiliary_input_tap;
}

//================================================================================================

template<typename tinyram_r1cs_params>
bool
tinyram_circuit<tinyram_r1cs_params>::initial_boot_trace(const std::string& primary_input_path) {
  std::ifstream f_primary_input(primary_input_path);
  libff::enter_block("Loading primary input");
  tinyram_snark::tinyram_input_tape primary_input(tinyram_snark::load_tape(f_primary_input));
  libff::leave_block("Loading primary input");
  const size_t boot_trace_size_bound = this->bounds["tinyram_input_size_bound"] + this->bounds["tinyram_program_size_bound"];
  try{
    this->boot_trace = tinyram_boot_trace_from_program_and_input(this->tinyram_ap, boot_trace_size_bound, program, primary_input);
    return true;
  }
  catch (std::exception &e){
    return false;
  }
}

template<typename tinyram_r1cs_params>
tinyram_snark::ram_architecture_params<typename tinyram_r1cs_params::machine_pp>&
tinyram_circuit<tinyram_r1cs_params>::get_ram_architecture_params(){
  return this->tinyram_ap;
};

/*Return ture if auxiliary input is read into the tinyram_circuit
 * Input: auxiliary input file path
 * the client must call 'get_aux_input' after ensuring that this function has been called
 */
template<typename tinyram_r1cs_params>
bool tinyram_circuit<tinyram_r1cs_params>::initial_aux_input(const std::string &aux_input_path) {
  try{
    std::ifstream aux(aux_input_path);
    libff::enter_block("Loading auxiliary input");
    auxiliary_input_tap = tinyram_snark::load_tape(aux);
    libff::leave_block("Loading auxiliary input");
    return true;
  }
  catch (std::exception &e){
    return false;
  }
}
// initial the
template<typename tinyram_r1cs_params>
tinyram_circuit<tinyram_r1cs_params>::tinyram_circuit(std::unique_ptr<params_config> config) {
  //inital ap
  tinyram_snark::ram_architecture_params<typename tinyram_r1cs_params::machine_pp> ap(config->get_word_size(),config->get_register_count());
  this->tinyram_ap = std::move(ap);
  // initial program
  std::istringstream  vp_stream(config->get_verify_program());
  this->program = load_preprocessed_program(tinyram_ap, vp_stream);
  //initial bound
  this->bounds["tinyram_input_size_bound"] = config->get_tinyram_input_size_bound();
  this->bounds["tinyram_program_size_bound"] =  config->get_tinyram_program_size_bound();
  this->bounds["time_bound"] =  config->get_time_bound();
}
}