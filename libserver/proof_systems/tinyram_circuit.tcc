//
// Created by alittlehorse on 3/16/21.
//

#include <string>
#include <istream>
#include <fstream>
#include <optional>
#include "tinyram_circuit.hpp"


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


    //================================================================================================
    template<typename tinyram_r1cs_params>
    tinyram_circuit<tinyram_r1cs_params>::tinyram_circuit(const std::string& assemble_file_name,
                                                             const std::string& bounds_path,
                                                             const std::string&  architecture_params_path,
                                                             const std::string& primary_input_path,
                                                             const std::string& auxiliary_input_path):
    assemble_file_name(assemble_file_name),
    bounds_path(bounds_path),
    architecture_params_path(architecture_params_path),
    primary_input_path(primary_input_path),
    auxiliary_input_path(auxiliary_input_path){
        tinyram_r1cs_params::init_public_params();
        libff::start_profiling();
        assert(set_ram_architecture_params(this->architecture_params_path)==true);
        assert(set_bounds(this->bounds_path)==true);
        //assert(set_program(this->assemble_file_name,this->tinyram_ap)==true);
        assert(set_program(this->assemble_file_name,this->tinyram_ap)==true);
        assert(set_boot_trace(this->primary_input_path)==true);
        assert(set_aux_input(this->auxiliary_input_path)==true);
    }

    template<typename tinyram_r1cs_params>
    bool
    tinyram_circuit<tinyram_r1cs_params>::set_bounds(const std::string &bounds_path) {
        size_t tinyram_input_size_bound, tinyram_program_size_bound, time_bound;
        try{
            std::ifstream f_rp(bounds_path);
            f_rp >> tinyram_input_size_bound >> tinyram_program_size_bound >> time_bound;
        }
        catch(std::exception &e){
            return false;
        }
        this->bounds["tinyram_input_size_bound"] = tinyram_input_size_bound;
        this->bounds["tinyram_program_size_bound"] = tinyram_program_size_bound;
        this->bounds["time_bound"] = time_bound;

        return true;
    }



    template<typename tinyram_r1cs_params>
    bool tinyram_circuit<tinyram_r1cs_params>::set_ram_architecture_params(const std::string &architecture_params_file_path) {
        tinyram_snark::ram_architecture_params<typename tinyram_r1cs_params::machine_pp> ap;
        try{
            std::ifstream f_ap(architecture_params_file_path);
            f_ap >> ap;
        }
        catch(std::exception &e){
            return false;
        }
        this->tinyram_ap = std::move(ap);
        return true;
    }


    template<typename tinyram_r1cs_params>
    bool
    tinyram_circuit<tinyram_r1cs_params>::set_boot_trace(const std::string& primary_input_path) {
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

    template<typename tinyram_r1cs_params>
    bool tinyram_circuit<tinyram_r1cs_params>::set_program(
            const std::string& assemble_file_path,
            const tinyram_snark::ram_architecture_params<typename tinyram_r1cs_params::machine_pp>& ap)
            {
                try{
                    std::ifstream processed(assemble_file_path);
                    this->program = load_preprocessed_program(ap, processed);
                }
                catch (std::exception &e){
                    return false;
                }
                return true;
            }

    template<typename tinyram_r1cs_params>
    bool tinyram_circuit<tinyram_r1cs_params>::set_aux_input(const std::string &aux_input_path) {
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

    template<typename tinyram_r1cs_params>
    const tinyram_snark::tinyram_input_tape &tinyram_circuit<tinyram_r1cs_params>::get_auxiliary_input_tap() {
        return auxiliary_input_tap;
    }


}