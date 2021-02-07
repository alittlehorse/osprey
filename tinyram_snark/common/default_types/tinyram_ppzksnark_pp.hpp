/** @file
 *****************************************************************************

 This file defines the default architecture and curve choices for RAM
 ppzk-SNARK.

 *****************************************************************************/

#ifndef TINYRAM_PPZKSNARK_PP_HPP_
#define TINYRAM_PPZKSNARK_PP_HPP_

#include <tinyram_snark/common/default_types/r1cs_ppzksnark_pp.hpp>
#include <tinyram_snark/relations/ram_computations/rams/tinyram/tinyram_params.hpp>

namespace tinyram_snark {

class default_tinyram_ppzksnark_pp {
public:
    typedef default_r1cs_ppzksnark_pp snark_pp;
    typedef libff::Fr<default_r1cs_ppzksnark_pp> FieldT;
    typedef ram_tinyram<FieldT> machine_pp;

    static void init_public_params();
};

} // tinyram_snark

#endif // TINYRAM_PPZKSNARK_PP_HPP_
