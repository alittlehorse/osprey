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
#ifndef OSPREY_PROOF_PUBLIC_PARAMS_H
#define OSPREY_PROOF_PUBLIC_PARAMS_H
#include <string>
#include <libserver/proof_systems/tinyram_r1cs_pp.hpp>
#include <libserver/aux_struct/params_config.hpp>
#include <tinyram_snark/relations/ram_computations/rams/tinyram/tinyram_params.hpp>
#include <unordered_map>
#include<optional>
#include <fstream>
namespace libserver{


    template<typename tinyram_r1cs_params>
    class tinyram_circuit {
     public:
      typedef typename tinyram_r1cs_params::machine_pp machine_pp;

      tinyram_circuit() = delete;
      explicit tinyram_circuit(std::unique_ptr<params_config> config);

      tinyram_snark::ram_architecture_params<machine_pp>& get_ram_architecture_params();
      const std::unordered_map<const char*,size_t>&get_bounds();
      const tinyram_snark::tinyram_program& get_tinyram_program();
      const tinyram_snark::ram_boot_trace<machine_pp>& get_boot_trace();
      const tinyram_snark::tinyram_input_tape& get_auxiliary_input_tap();

      bool initial_boot_trace(const std::string& primary_input_path);
      bool initial_aux_input(const std::string &aux_input_path);
     private:
      tinyram_snark::ram_architecture_params<machine_pp> tinyram_ap;
      std::unordered_map<const char*,size_t> bounds={{"tinyram_input_size_bound",-1},{"tinyram_program_size_bound",-1},
                                                     {"time_bound",-1}};
      tinyram_snark::tinyram_program program;
      tinyram_snark::ram_boot_trace<machine_pp> boot_trace;
      tinyram_snark::tinyram_input_tape auxiliary_input_tap;
      const std::string primary_input_path;
      const std::string auxiliary_input_path;
    };


}
#include <libserver/proof_systems/tinyram_circuit.tcc>
#endif //OSPREY_PROOF_PUBLIC_PARAMS_H
