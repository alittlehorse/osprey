/** @file
 *****************************************************************************
 * @author     This file is part of tinyram_snark, developed by SCIPR Lab
 *             and contributors (see AUTHORS).
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/

#ifndef SIMPLE_EXAMPLE_HPP_
#define SIMPLE_EXAMPLE_HPP_

#include <tinyram_snark/relations/constraint_satisfaction_problems/r1cs/examples/r1cs_examples.hpp>

namespace tinyram_snark {

template<typename FieldT>
r1cs_example<FieldT> gen_r1cs_example_from_protoboard(const size_t num_constraints,
                                                      const size_t num_inputs);

} // tinyram_snark

#include <tinyram_snark/gadgetlib1/examples/simple_example.tcc>

#endif // SIMPLE_EXAMPLE_HPP_
