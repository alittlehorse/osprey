/** @file
 *****************************************************************************
 Declaration of interface for the proof params config.
 Given the config file path, which is coded by json format, proof_params_config parse all params included in this file.
 the config file should be in the following form:
 {
    "architecture params":{
        "register_count":16,
        "word_size":16,
    },
    tinyram_input_size_bound: 24,
    time_bound: 40,
    tinyram_program_size_bound:25,
    program:"import sys; ....."
    verify_program:"mov r1 1; ...."
 }
 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/

#ifndef OSPREY_proof_program_H
#define OSPREY_proof_program_H


#include<boost/json.hpp>


namespace libserver{

    class proof_params_config{
     private:


        std::string processed_assembly_fn;
        std::string architecture_params_fn;
        std::string computation_bounds_fn;
        std::string primary_input_fn;
        std::string auxiliary_input_fn;
        std::string _program_name;
        std::string proving_key_path;
        std::string verification_key_path;
        std::string proof_path;
        std::string log_path;

     public:
      [[nodiscard]] const std::string& get_processed_assembly_path()const;
      [[nodiscard]] const std::string& get_architecture_params_path() const;
      [[nodiscard]] const std::string& get_computation_bounds_path() const;
      [[nodiscard]] const std::string& get_primary_input_path() const;
      [[nodiscard]] const std::string& get_auxiliary_input_path() const;
      [[nodiscard]] const std::string& get_program_name() const;
      [[nodiscard]] const std::string& get_log_path() const;
      [[nodiscard]] const std::string& get_proving_key_path() const;
      [[nodiscard]] const std::string& get_verification_key_path() const;
      [[nodiscard]] const std::string& get_proof_path() const;
        proof_params_config()=delete;
        explicit proof_params_config(const std::string& program_name);
    };
}
#endif //OSPREY_proof_program_H