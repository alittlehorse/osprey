/** @file
 *****************************************************************************

 Declaration of interfaces for a proof program provided by server requester

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/
#include <string>
#include <utility>
#include <libserver/aux_struct/proof_params_config.hpp>
namespace libserver{
    proof_params_config::proof_params_config(const std::string&& program_name) {
        _program_name = program_name;
        processed_assembly_fn = _program_name +"/"+"processed_assembly.txt";
        architecture_params_fn = _program_name +"/"+ "architecture_params.txt";
        primary_input_fn = _program_name +"/"+ "primary_input.txt";
        auxiliary_input_fn = _program_name +"/"+ "auxiliary_input.txt";
        computation_bounds_fn = _program_name +"/"+ "computation_bounds.txt";
        log_path = _program_name +"/"+ "log.txt";
        proving_key_path = _program_name +"/"+ "proving_key";
        verification_key_path = _program_name +"/"+ "verification_key";
        proof_path = _program_name +"/"+ "proof";
    }

    const std::string& proof_params_config::get_architecture_params_path()const {
        return architecture_params_fn;
    }

    const std::string& proof_params_config::get_auxiliary_input_path()const {
        return auxiliary_input_fn;
    }

    const std::string& proof_params_config::get_computation_bounds_path()const{
    return computation_bounds_fn;
}
    const std::string & proof_params_config::get_primary_input_path()const{
    return primary_input_fn;
}

    const std::string& proof_params_config::get_processed_assembly_path() const{
    return processed_assembly_fn;
}
    const std::string& proof_params_config::get_program_name() const{
        return _program_name;
    }

    const std::string& proof_params_config::get_log_path() const{
        return log_path;
    }

    const std::string &proof_params_config::get_proving_key_path() const {
        return proving_key_path;
    }

    const std::string &proof_params_config::get_verification_key_path() const {
        return verification_key_path;
    }

    const std::string &proof_params_config::get_proof_path() const {
        return proof_path;
    }
}
