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
#include <tinyram_snark/relations/constraint_satisfaction_problems/r1cs/r1cs.hpp>
#include <tinyram_snark/relations/ram_computations/rams/tinyram/tinyram_aux.hpp>
#include <optional>
#include <libserver/ram_compiler/specialization_pool.hpp>


namespace libserver {

    template<typename tinyram_r1cs_params>
    class tinyram_compiler_server {

    public:
        /// complie the tinyram file to immediate format.
        /// \arg:: file_path:std::string&&
        /// \return: bool and write the immediate format to the same path
        using   machine_pp =typename tinyram_r1cs_params::machine_pp;
        using   FieldT = typename tinyram_r1cs_params::FieldT;


        /// construct a tinyram compiler ,instance ram_to_r1cs
        /// \param ap
        /// \param boot_trace_size_bound
        /// \param time_bound
        tinyram_compiler_server(const std::string& log_path);


        bool specialization(const tinyram_snark::ram_architecture_params<machine_pp> &ap,
                            const size_t boot_trace_size_bound,
                            const size_t time_bound);
        std::optional<tinyram_snark::r1cs_constraint_system<FieldT>>
        compile_r1cs_constrain_system();

        std::optional<tinyram_snark::r1cs_primary_input<FieldT>>
        compile_r1cs_primary_input(tinyram_snark::ram_boot_trace<typename tinyram_r1cs_params::machine_pp>& boot_trace);

        std::optional<tinyram_snark::r1cs_auxiliary_input<FieldT>>
        compile_r1cs_auxiliary_input(tinyram_snark::ram_boot_trace<typename tinyram_r1cs_params::machine_pp>& boot_trace,
                                      const tinyram_snark::tinyram_input_tape& aux_input);
    private:
        tinyram_compiler_server()=default;
        Log *log;
        tinyram_snark::ram_to_r1cs<machine_pp>* ram2r1cs;
        specialization_factor sf;
    };

}
#include <libserver/ram_compiler/tinyram_compiler_server.tcc>


#endif //OSPREY_TINYRAM_COMPLIER_SERVER_H
