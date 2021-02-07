/** @file
 *****************************************************************************

 This file defines default_r1cs_ppzksnark_pp based on the elliptic curve
 choice selected in ec_pp.hpp.

 *****************************************************************************/

#ifndef R1CS_PPZKSNARK_PP_HPP_
#define R1CS_PPZKSNARK_PP_HPP_

#include <libff/common/default_types/ec_pp.hpp>

namespace tinyram_snark {
typedef libff::default_ec_pp default_r1cs_ppzksnark_pp;
} // tinyram_snark

#endif // R1CS_PPZKSNARK_PP_HPP_
