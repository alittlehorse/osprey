/** @file
 *****************************************************************************
 Declaration of PublicParams for Fp field arithmetic
 *****************************************************************************
 * @author     This file is part of tinyram_snark, developed by SCIPR Lab
 *             and contributors (see AUTHORS).
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/

#ifndef tinyram_snark_GADGETLIB2_INCLUDE_GADGETLIB2_PP_HPP_
#define tinyram_snark_GADGETLIB2_INCLUDE_GADGETLIB2_PP_HPP_

#include <memory>
#include <vector>

#include <libff/common/default_types/ec_pp.hpp>

namespace gadgetlib2 {

/*************************************************************************************************/
/*************************************************************************************************/
/*******************                                                            ******************/
/*******************                        R1P World                           ******************/
/*******************                                                            ******************/
/*************************************************************************************************/
/*************************************************************************************************/

/* curve-specific public parameters */
typedef libff::Fr<libff::default_ec_pp> Fp;

typedef std::vector<Fp> FpVector;

class PublicParams {
public:
    size_t log_p;
    PublicParams(const std::size_t log_p);
    Fp getFp(long x) const; // to_support changes later
    ~PublicParams();
};

PublicParams initPublicParamsFromDefaultPp();

} // namespace gadgetlib2
#endif // tinyram_snark_GADGETLIB2_INCLUDE_GADGETLIB2_PP_HPP_
