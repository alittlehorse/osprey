/** @file
 *****************************************************************************

 Declaration of interfaces for a proof program provided by server requester

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/
#include <string>
#include <utility>
#include <libserver/aux/proof_params_config.hpp>
namespace libserver{
    proof_params_config::proof_params_config(std::string program_name) {
        _program_name = std::move(program_name);
        processe_program();
    }

    std::string proof_params_config::get_architecture_params_fn() {
        return architecture_params_fn;
    }

    std::string proof_params_config::get_auxiliary_input_fn() {
        return auxiliary_input_fn;
    }

    std::string proof_params_config::get_computation_bounds_fn(){
    return computation_bounds_fn;
}
std::string proof_params_config::get_primary_input_fn(){
    return primary_input_fn;
}

std::string proof_params_config::get_processed_assembly_fn(){
    return processed_assembly_fn;
}
std::string proof_params_config::get_program_name(){
        return _program_name;
    }
}
