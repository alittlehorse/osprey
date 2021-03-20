/** @file
 *****************************************************************************

 Declaration of interfaces for compling the proof program which source langrauge is tinyram

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/

#ifndef OSPREY_TINYRAM_COMPLIER_SERVER_H
#define OSPREY_TINYRAM_COMPLIER_SERVER_H
#include <unordered_map>
#include <vector>
#include <libserver/aux/Log.hpp>
#include <tinyram_snark/reductions/ram_to_r1cs/ram_to_r1cs.hpp>
#include <tinyram_snark/common/default_types/r1cs_gg_ppzksnark_pp.hpp>
#include <optional>
#include <tinyram_snark/relations/constraint_satisfaction_problems/r1cs/r1cs.hpp>

namespace libserver {

    /// tinyram_complier
    template<typename tinyram_r1cs_params>
    class tinyram_complier_server {
        //input the assemble file and process the file ,like a complier
    public:
        /// complie the tinyram file to immediate format.
        /// \arg:: file_path:std::string&&
        /// \return: bool and write the immediate format to the same path
        using   machine_pp =typename tinyram_r1cs_params::machine_pp;
        using   FieldT = typename tinyram_r1cs_params::FieldT;


        std::optional<tinyram_snark::r1cs_constraint_system<FieldT>>
        complie_r1cs_constrain_system(const tinyram_snark::ram_architecture_params<machine_pp> &ap,
                     const std::unordered_map<const char *, size_t> &bounds);

        std::optional<tinyram_snark::r1cs_primary_input<FieldT>> compiler_r1cs_primary_input();
        std::optional<tinyram_snark::r1cs_auxiliary_input<FieldT>> compiler_r1cs_auxiliary_input();
    private:

        Log *log;
        tinyram_snark::ram_to_r1cs<machine_pp> r;


    };



}
#include <libserver/ram_complier/tinyram_complier_server.tcc>


#endif //OSPREY_TINYRAM_COMPLIER_SERVER_H
