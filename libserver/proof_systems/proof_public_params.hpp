//
// Created by alittlehorse on 3/16/21.
//

#ifndef OSPREY_PROOF_PUBLIC_PARAMS_H
#define OSPREY_PROOF_PUBLIC_PARAMS_H
#include<string>
#include<libserver/proof_systems/tinyram_zksnark_pp.hpp>
#include <tinyram_snark/relations/ram_computations/rams/tinyram/tinyram_params.hpp>
#include <unordered_map>
#include<optional>
#include <fstream>
namespace libserver{
    template<typename ppT>
    class proof_public_params {
    private:
        std::string ppid;
        tinyram_snark::ram_architecture_params<typename _tinyram_zksnark_pp::machine_pp> tinyram_ap;
        std::unordered_map<const char*,size_t> bounds={
                {"tinyram_input_size_bound",-1},
                {"tinyram_program_size_bound",-1},
                {"time_bound",-1}
        };
        tinyram_snark::tinyram_program program;
        tinyram_snark::ram_boot_trace<typename _tinyram_zksnark_pp::machine_pp> boot_trace;

        const std::string file_path;
        const std::string assemble_file_name;
        const std::string bounds_path;
        const std::string architecture_params_path;
        const std::string primary_input_path;

        bool set_ram_architecture_params(const std::string& architecture_params_file_path);
        bool set_program(
                const std::string& assemble_file_path,
                const tinyram_snark::ram_architecture_params<typename _tinyram_zksnark_pp::machine_pp>& ap
                );
        bool set_bounds(const std::string &bounds_path);

        bool set_boot_trace(const std::string& primary_input_path);

        proof_public_params(){};

    public:
        typedef tinyram_zksnark_pp<ppT> _tinyram_zksnark_pp;
        proof_public_params(std::string&& assemble_file_name,
                            std::string&& bounds_path,
                            std::string&& architecture_params_path,
                            std::string&& primary_input_path);

        tinyram_snark::ram_architecture_params<typename _tinyram_zksnark_pp::machine_pp>
        get_ram_architecture_params();

        const std::unordered_map<const char*,size_t>
        get_bounds();

        const tinyram_snark::tinyram_program
        get_tinyram_program();

        const tinyram_snark::ram_boot_trace<typename _tinyram_zksnark_pp::machine_pp>
        get_boot_trace();

    };


}
#include <libserver/proof_systems/proof_public_params.tcc>
#endif //OSPREY_PROOF_PUBLIC_PARAMS_H
