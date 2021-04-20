/** @file
 *****************************************************************************

 Declaration of interfaces for a proof program config provided by server requester

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/

#ifndef OSPREY_proof_program_H
#define OSPREY_proof_program_H





namespace libserver{

    class proof_params_config{
        private:
        std::string processed_assembly_fn;
        std::string architecture_params_fn;
        std::string computation_bounds_fn;
        std::string primary_input_fn;
        std::string auxiliary_input_fn;
        std::string _program_name;
        std::string log_path;
        std::string proving_key_path;
        std::string verification_key_path;
        std::string proof_path;

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

        bool set_processed_assembly_fn(const std::string&& processed_assemble_path);
        bool set_architecture_params_fn(const std::string&& architecture_params_fn);
        bool set_computation_bounds_fn(const std::string&& computation_bounds_fn);
        bool set_primary_input_fn(const std::string&& _primary_input_fn);
        bool set_get_auxiliary_input_path(const std::string&& get_auxiliary_input_path);
        proof_params_config()=default;
        explicit proof_params_config(const std::string&& program_name);
    };
}
#endif //OSPREY_proof_program_H