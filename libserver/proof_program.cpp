/** @file
 *****************************************************************************

 Declaration of interfaces for a proof program provided by server requester

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/
#include <string>
#include <utility>
#include <libserver/proof_program.hpp>
namespace libserver{
    proof_program::proof_program(std::string program_name) {
        _program_name = std::move(program_name);
        processe_program();
    }

    std::string proof_program::get_architecture_params_fn() {
        return architecture_params_fn;
    }
    std::string proof_program::get_assembly_fn() {
        return assembly_fn;
    }
    std::string proof_program::get_auxiliary_input_fn() {
        return auxiliary_input_fn;
    }

    std::string proof_program::get_computation_bounds_fn(){
    return computation_bounds_fn;
}
std::string proof_program::get_primary_input_fn(){
    return primary_input_fn;
}

std::string proof_program::get_processed_assembly_fn(){
    return processed_assembly_fn;
}
std::string proof_program::get_program_name(){
        return _program_name;
    }
}
