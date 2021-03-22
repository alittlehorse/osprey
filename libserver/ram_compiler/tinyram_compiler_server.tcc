/** @file
 *****************************************************************************

 Declaration of interfaces for compling the proof program which source langrauge is tinyram

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/
#include <regex>
#include <fstream>
#include <cassert>
#include <string>
#include <functional>
#include <tinyram_snark/reductions/ram_to_r1cs/ram_to_r1cs.hpp>

namespace libserver {
    template<typename tinyram_r1cs_params>
    std::optional<tinyram_snark::r1cs_constraint_system<typename tinyram_r1cs_params::FieldT>>
    tinyram_compiler_server<tinyram_r1cs_params>::compile_r1cs_constrain_system()
    {
        try {
            ram2r1cs->instance_map();
            tinyram_snark::r1cs_constraint_system<typename tinyram_r1cs_params::FieldT> constraint_system = ram2r1cs->get_constraint_system();
            log->write_log("the complier from ram to r1cs is success!\n\n");
            return {constraint_system};
        }
        catch (std::exception &e) {
            log->write_log("From Ram to R1CS compling failed!\n\n");
            return std::nullopt;
        }
    }

    template<typename tinyram_r1cs_params>
    tinyram_compiler_server<tinyram_r1cs_params>::tinyram_compiler_server(const std::string& log_path){
        log = new Log(log_path);
    }


    template<typename tinyram_r1cs_params>
    std::optional<tinyram_snark::r1cs_primary_input<typename tinyram_r1cs_params::FieldT>>
    tinyram_compiler_server<tinyram_r1cs_params>::compile_r1cs_primary_input(tinyram_snark::ram_boot_trace<typename tinyram_r1cs_params::machine_pp>& boot_trace
            ){
        try{
            tinyram_snark::r1cs_primary_input<typename tinyram_r1cs_params::FieldT> primary_input= ram2r1cs->primary_input_map(sf.get_ram_architecture_params(), sf.get_boot_trace_size_bound(), boot_trace);
            return {primary_input};
        }
        catch (std::exception &e){
            return std::nullopt;
        }

    }

    template<typename tinyram_r1cs_params>
    std::optional<tinyram_snark::r1cs_auxiliary_input<typename tinyram_r1cs_params::FieldT>>
    tinyram_compiler_server<tinyram_r1cs_params>::compile_r1cs_auxiliary_input(
            tinyram_snark::ram_boot_trace<typename tinyram_r1cs_params::machine_pp>& boot_trace,
            const tinyram_snark::tinyram_input_tape& aux_input) {
        try{
            auto auxiliary_input = ram2r1cs->auxiliary_input_map(boot_trace, aux_input);
            return {auxiliary_input};
        }
        catch(std::exception &e){
            return std::nullopt;
        }
    }


    template<typename tinyram_r1cs_params>
    bool tinyram_compiler_server<tinyram_r1cs_params>::specialization(const tinyram_snark::ram_architecture_params<typename tinyram_r1cs_params::machine_pp> &ap,
                                                                      const size_t boot_trace_size_bound,
                                                                      const size_t time_bound) {
        try{
            sf = *(new specialization_factor(ap,boot_trace_size_bound,time_bound));
            if(specialization_pool<typename tinyram_r1cs_params::machine_pp>::has_contained(sf)) {
                ram2r1cs = specialization_pool<typename tinyram_r1cs_params::machine_pp>::get_r1cs_constraint_system(sf).value();
            }
            else{
                ram2r1cs = new tinyram_snark::ram_to_r1cs<typename tinyram_r1cs_params::machine_pp>(
                        sf.get_ram_architecture_params(), sf.get_boot_trace_size_bound(),
                        sf.get_time_bound());
                if(!specialization_pool<typename tinyram_r1cs_params::machine_pp>::push_r1cs_constraint_system_into_pool(sf,ram2r1cs))return false;
            }
            return true;
        }
        catch (std::exception &e){
            return false;
        }
    }

    /*  template<typename ppT>
      std::optional<tinyram_snark::r1cs_constraint_system<libff::Fr<ppT>>>
      tinyram_compiler_server::complie_r1cs(std::string &&architecture_params_path,
                                            std::string &&computation_bounds_path) {
          typedef tinyram_snark::ram_tinyram<ppT> default_ram_with_pp;
          ppT::init_public_params();

          tinyram_snark::ram_architecture_params<default_ram_with_pp> ap;
          std::ifstream f_ap(architecture_params_path);
          f_ap >> ap;

          log->write_log(fmt::format("Will run on %zu register machine (word size = %zu)\n", ap.k, ap.w));

          std::ifstream f_rp(computation_bounds_path);
          size_t tinyram_input_size_bound, tinyram_program_size_bound, time_bound;
          f_rp >> tinyram_input_size_bound >> tinyram_program_size_bound >> time_bound;
          const size_t boot_trace_size_bound = tinyram_input_size_bound + tinyram_program_size_bound;

          typedef tinyram_snark::default_tinyram_gg_ppzksnark_pp::machine_pp default_ram_with_Fr;
          try {
              tinyram_snark::ram_to_r1cs<default_ram_with_Fr> r(ap, boot_trace_size_bound, time_bound);
              r.instance_map();

              tinyram_snark::r1cs_constraint_system<default_ram_with_Fr::base_field_type> constraint_system = r.get_constraint_system();
              log->write_log("the complier from ram to r1cs is success!\n\n");
              return {constraint_system};
          }
          catch (exception &e) {
              log->write_log("From Ram to R1CS compling failed!\n\n");
              return nullopt;
          }

      }*/

 
}