/** @file
 *****************************************************************************

Declaration of interface of tinyram_r1cs_pp
 public params for tinyram,r1cs and Conversion form from A to B.
 include:
 ppT
 FieldT
 ram_tinyram<FieldT>

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/
#ifndef TINYRAM_ZKSNARK_PP
#define TINYRAM_ZKSNARK_PP
#include <tinyram_snark/common/default_types/r1cs_gg_ppzksnark_pp.hpp>
#include <tinyram_snark/relations/ram_computations/rams/tinyram/tinyram_params.hpp>
namespace libserver{
    template<typename ppT>
    class tinyram_r1cs_pp{
    public:
        typedef ppT snark_pp;
        typedef libff::Fr<ppT> FieldT;
        typedef tinyram_snark::ram_tinyram<FieldT> machine_pp;

        static void init_public_params(){
            snark_pp::init_public_params();
        }
    };

}
#endif

