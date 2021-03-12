/** @file
 *****************************************************************************

the server of zksnark using the Groth16 algorithm
 + generate_proof
 + test_proof
 + generate keypair
 + generate architecture params
 + get bounds(time bounds, compution bounds...)

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/



#ifndef OSPREY_GROTH16_SERVER_HPP
#define OSPREY_GROTH16_SERVER_HPP

#include <tinyram_snark/common/default_types/tinyram_gg_ppzksnark_pp.hpp>
#include <tinyram_snark/reductions/ram_to_r1cs/ram_to_r1cs.hpp>
#include <tinyram_snark/relations/ram_computations/rams/tinyram/tinyram_params.hpp>
#include <tinyram_snark/zk_proof_systems/r1cs_gg_ppzksnark/r1cs_gg_ppzksnark.hpp>

#include <libserver/ram_complier/tinyram_complier_server.hpp>
#include <libserver/proof_program.hpp>
#include <libserver/Log.hpp>
#include <unordered_map>

using namespace tinyram_snark;
namespace  libserver{
    class groth16_server {
    public:
        bool construct_proof();
        groth16_server(proof_program& v) {
            _vp = v;
            log = new Log(v.get_program_name()+"/"+v.get_program_name()+"_log.txt");
        }
        template<typename ramT>
        std::optional<const ram_architecture_params<ramT>> generate_ram_architecture_params(std::string&& file_path);

        std::optional<const std::tuple<size_t,size_t,size_t>> get_bounds(std::string&& bounds_filepath);

        std::optional<tinyram_program> generate_program(std::string&& processed_assemble_filepath,const tinyram_architecture_params& ap);


    private:
        proof_program _vp;
        Log* log;
    };
}


#include <libserver/proof_systems/groth16_server.tcc>


#endif //OSPREY_GROTH16_SERVER_HPP


