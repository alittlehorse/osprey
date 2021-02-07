/** @file
 *****************************************************************************
 * @author     This file is part of tinyram_snark, developed by SCIPR Lab
 *             and contributors (see AUTHORS).
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/

#include <tinyram_snark/gadgetlib2/adapters.hpp>
#include <tinyram_snark/gadgetlib2/examples/simple_example.hpp>
#include <tinyram_snark/gadgetlib2/gadget.hpp>
#include <tinyram_snark/gadgetlib2/integration.hpp>

namespace tinyram_snark {

/* NOTE: all examples here actually generate one constraint less to account for soundness constraint in QAP */
r1cs_example<libff::Fr<libff::default_ec_pp> > gen_r1cs_example_from_gadgetlib2_protoboard(const size_t size)
{
    typedef libff::Fr<libff::default_ec_pp> FieldT;

    gadgetlib2::initPublicParamsFromDefaultPp();
    // necessary in case a protoboard was built before,  tinyram_snark assumes variable indices always
    // begin with 0 so we must reset the index before creating constraints which will be used by
    // tinyram_snark
    gadgetlib2::GadgetLibAdapter::resetVariableIndex();

    // create a gadgetlib2 gadget. This part is done by both generator and prover.
    auto pb = gadgetlib2::Protoboard::create(gadgetlib2::R1P);
    gadgetlib2::VariableArray A(size, "A");
    gadgetlib2::VariableArray B(size, "B");
    gadgetlib2::Variable result("result");
    auto g = gadgetlib2::InnerProduct_Gadget::create(pb, A, B, result);
    // create constraints. This part is done by generator.
    g->generateConstraints();
    // create assignment (witness). This part is done by prover.
    for (size_t k = 0; k < size; ++k)
    {
        pb->val(A[k]) = std::rand() % 2;
        pb->val(B[k]) = std::rand() % 2;
    }
    g->generateWitness();
    // translate constraint system to tinyram_snark format.
    r1cs_constraint_system<FieldT> cs = get_constraint_system_from_gadgetlib2(*pb);
    // translate full variable assignment to tinyram_snark format
    const r1cs_variable_assignment<FieldT> full_assignment = get_variable_assignment_from_gadgetlib2(*pb);
    // extract primary and auxiliary input
    const r1cs_primary_input<FieldT> primary_input(full_assignment.begin(), full_assignment.begin() + cs.num_inputs());
    const r1cs_auxiliary_input<FieldT> auxiliary_input(full_assignment.begin() + cs.num_inputs(), full_assignment.end());

    assert(cs.is_valid());
    assert(cs.is_satisfied(primary_input, auxiliary_input));

    return r1cs_example<FieldT>(cs, primary_input, auxiliary_input);
}

} // tinyram_snark

