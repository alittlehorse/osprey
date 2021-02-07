/** @file
 *****************************************************************************

 Declaration of functionality that runs the R1CS ppzkSNARK for
 a given R1CS example.

 *****************************************************************************
 * @author     This file is part of tinyram_snark, developed by SCIPR Lab
 *             and contributors (see AUTHORS).
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/

#ifndef RUN_R1CS_PPZKSNARK_HPP_
#define RUN_R1CS_PPZKSNARK_HPP_

#include <libff/common/default_types/ec_pp.hpp>

#include <tinyram_snark/relations/constraint_satisfaction_problems/r1cs/examples/r1cs_examples.hpp>

namespace tinyram_snark {

/**
 * Runs the ppzkSNARK (generator, prover, and verifier) for a given
 * R1CS example (specified by a constraint system, input, and witness).
 *
 * Optionally, also test the serialization routines for keys and proofs.
 * (This takes additional time.)
 */
template<typename ppT>
bool run_r1cs_ppzksnark(const r1cs_example<libff::Fr<ppT> > &example,
                        const bool test_serialization);

} // tinyram_snark

#include <tinyram_snark/zk_proof_systems/ppzksnark/r1cs_ppzksnark/examples/run_r1cs_ppzksnark.tcc>

#endif // RUN_R1CS_PPZKSNARK_HPP_
