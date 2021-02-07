/** @file
 *****************************************************************************
 * @author     This file is part of tinyram_snark, developed by SCIPR Lab
 *             and contributors (see AUTHORS).
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/

#ifndef SIMPLE_EXAMPLE_HPP_
#define SIMPLE_EXAMPLE_HPP_

#include <libff/common/default_types/ec_pp.hpp>

#include <tinyram_snark/relations/constraint_satisfaction_problems/r1cs/examples/r1cs_examples.hpp>

namespace tinyram_snark {

r1cs_example<libff::Fr<libff::default_ec_pp> > gen_r1cs_example_from_gadgetlib2_protoboard(const size_t size);

} // tinyram_snark

#endif // SIMPLE_EXAMPLE_HPP_
