/** @file
 *****************************************************************************
 * @author     This file is part of tinyram_snark, developed by SCIPR Lab
 *             and contributors (see AUTHORS).
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/

#ifndef INTEGRATION_HPP_
#define INTEGRATION_HPP_

#include <libff/common/default_types/ec_pp.hpp>

#include <tinyram_snark/gadgetlib2/protoboard.hpp>
#include <tinyram_snark/relations/constraint_satisfaction_problems/r1cs/r1cs.hpp>

namespace tinyram_snark {

r1cs_constraint_system<libff::Fr<libff::default_ec_pp> > get_constraint_system_from_gadgetlib2(const gadgetlib2::Protoboard &pb);
r1cs_variable_assignment<libff::Fr<libff::default_ec_pp> > get_variable_assignment_from_gadgetlib2(const gadgetlib2::Protoboard &pb);

} // tinyram_snark

#endif // INTEGRATION_HPP_
