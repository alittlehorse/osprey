/** @file
 *****************************************************************************

 Declaration of interfaces for compling the proof program which source langrauge is tinyram

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/
#include <unordered_map>
#include <vector>
#include<tuple>
#include <libserver/Log.hpp>
#include <tinyram_snark/common/default_types/tinyram_gg_ppzksnark_pp.hpp>
#include <tinyram_snark/reductions/ram_to_r1cs/ram_to_r1cs.hpp>
#include <tinyram_snark/relations/ram_computations/rams/tinyram/tinyram_params.hpp>
#include <tinyram_snark/common/default_types/r1cs_gg_ppzksnark_pp.hpp>
#include<optional>

#ifndef OSPREY_TINYRAM_COMPLIER_SERVER_H
#define OSPREY_TINYRAM_COMPLIER_SERVER_H

using namespace std;
namespace libserver{

    /// tinyram_complier
    //template<typename ppT>
    class tinyram_comlier_server {
        //input the assemble file and process the file ,like a complier
    public:
        /// complie the tinyram file to mechism format
        /// arg:: file_path:std::string&&
        ///return: bool. if complie success, return ture

        const std::unordered_map<std::string,std::vector<std::string>> instruction_types=
                {       {"and",{"des","arg1","arg2"}},
                        {"or",{"des","arg1","arg2"}},
                        {"xor",{"des","arg1","arg2"}},
                        {"not",{"des","arg2"}},
                        {"add",{"des","arg1","arg2"}},
                        {"sub",{"des","arg1","arg2"}},
                        {"mull",{"des","arg1","arg2"}},
                        {"umulh",{"des","arg1","arg2"}},
                        {"smulh",{"des","arg1","arg2"}},
                        {"udiv",{"des","arg1","arg2"}},
                        {"umod",{"des","arg1","arg2"}},
                        {"shl",{"des","arg1","arg2"}},
                        {"shr",{"des","arg1","arg2"}},
                        {"cmpe",{"arg1","arg2"}},
                        {"cmpa",{"arg1","arg2"}},
                        {"cmpae",{"arg1","arg2"}},
                        {"cmpg",{"arg1","arg2"}},
                        {"cmpge",{"arg1","arg2"}},
                        {"mov",{"des","arg2"}},
                        {"cmov",{"des","arg2"}},
                        {"jmp",{"arg2"}},
                        {"cjmp",{"arg2"}},
                        {"cnjmp",{"arg2"}},
                        {"opcode_10111",{}},
                        {"opcode_11000",{}},
                        {"opcode_11001",{}},
                        {"store.b",{"arg2","des"}},
                        {"load.b",{"des","arg2"}},
                        {"store.w",{"arg2","des"}},
                        {"load.w",{"des","arg2"}},
                        {"read",{"des","arg2"}},
                        {"answer",{"arg2"}}};
        optional<tinyram_snark::tinyram_program> complie_tinyram(std::string &&file_path);

        template<typename ppT>
        optional<tinyram_snark::r1cs_constraint_system<libff::Fr<ppT>>> complie_r1cs(string &&architecture_params_path,string &&computation_bounds_path);

        bool tests();
    private:
        Log* log;
    };

}
#include <libserver/ram_complier/tinyram_complier_server.tcc>
#endif //OSPREY_TINYRAM_COMPLIER_SERVER_H
