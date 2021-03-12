//
// Created by alittlehorse on 3/8/21.
//

#ifndef LIBSNARK_TINYRAM_GG_PPZKSNARK_PP_HPP
#define LIBSNARK_TINYRAM_GG_PPZKSNARK_PP_HPP

#include <tinyram_snark/common/default_types/r1cs_gg_ppzksnark_pp.hpp>
#include <tinyram_snark/relations/ram_computations/rams/tinyram/tinyram_params.hpp>

namespace tinyram_snark {

    class default_tinyram_gg_ppzksnark_pp {
    public:
        typedef default_r1cs_gg_ppzksnark_pp snark_pp;
        typedef libff::Fr<default_r1cs_gg_ppzksnark_pp> FieldT;
        typedef ram_tinyram<FieldT> machine_pp;

        static void init_public_params(){
            snark_pp::init_public_params();
        }
    };
}
#endif //LIBSNARK_TINYRAM_GG_PPZKSNARK_PP_HPP
