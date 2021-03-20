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
#include<functional>




namespace libserver {
    template<typename tinyram_r1cs_params>
    std::optional<tinyram_snark::r1cs_constraint_system<typename tinyram_r1cs_params::FieldT>>
    tinyram_complier_server<tinyram_r1cs_params>::complie_r1cs_constrain_system(
            const tinyram_snark::ram_architecture_params <machine_pp> &ap, const std::unordered_map<const char *, size_t> &bounds)             {
        log->write_log(fmt::format("Will run on {} register machine (word size = {})\n", ap.k, ap.w));

        size_t tinyram_input_size_bound, tinyram_program_size_bound, time_bound;
        tinyram_input_size_bound = bounds.at("tinyram_input_size_bound");
        tinyram_program_size_bound = bounds.at("tinyram_program_size_bound");
        time_bound = bounds.at("time_bound");

        const size_t boot_trace_size_bound = tinyram_input_size_bound + tinyram_program_size_bound;
        //ap,bounds
        try {
            r.instance_map();

            tinyram_snark::r1cs_constraint_system<typename tinyram_r1cs_params::FieldT> constraint_system = r.get_constraint_system();
            log->write_log("the complier from ram to r1cs is success!\n\n");
            return {constraint_system};
        }
        catch (std::exception &e) {
            log->write_log("From Ram to R1CS compling failed!\n\n");
            return std::nullopt;
        }
    }


    template<typename tinyram_r1cs_params>
    std::optional<tinyram_snark::r1cs_primary_input<typename tinyram_r1cs_params::FieldT>> tinyram_complier_server<tinyram_r1cs_params>::compiler_r1cs_primary_input(){

        try{
            tinyram_snark::r1cs_primary_input<typename tinyram_r1cs_params::FieldT> primary_input= r.primary_input_map(ap, boot_trace_size_bound, boot_trace);
            return {primary_input};
        }
        catch (std::exception &e){
            return std::nullopt;
        }

    }


/*
 *
 *
    template<typename ppT>
    std::optional<tinyram_snark::r1cs_constraint_system<libff::Fr<ppT>>>
    tinyram_complier_server::complie_r1cs(std::string &&architecture_params_path,
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

    }

 * */
}