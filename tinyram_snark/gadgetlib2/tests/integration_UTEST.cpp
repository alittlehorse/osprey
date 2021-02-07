/** @file
 *****************************************************************************
 * @author     This file is part of tinyram_snark, developed by SCIPR Lab
 *             and contributors (see AUTHORS).
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/

#include <iostream>
#include <sstream>

#include "depends/gtest/googletest/include/gtest/gtest.h"

#include <tinyram_snark/common/default_types/r1cs_ppzksnark_pp.hpp>
#include <tinyram_snark/gadgetlib2/examples/simple_example.hpp>
#include <tinyram_snark/gadgetlib2/gadget.hpp>
#include <tinyram_snark/gadgetlib2/pp.hpp>
#include <tinyram_snark/gadgetlib2/protoboard.hpp>
#include <tinyram_snark/relations/constraint_satisfaction_problems/r1cs/examples/r1cs_examples.hpp>
#include <tinyram_snark/zk_proof_systems/ppzksnark/r1cs_ppzksnark/examples/run_r1cs_ppzksnark.hpp>

using namespace gadgetlib2;

namespace {

TEST(gadgetLib2,Integration) {
    using namespace tinyram_snark;

    initPublicParamsFromDefaultPp();
    const r1cs_example<libff::Fr<default_r1cs_ppzksnark_pp> > example = gen_r1cs_example_from_gadgetlib2_protoboard(100);
    const bool test_serialization = false;

    const bool bit = run_r1cs_ppzksnark<default_r1cs_ppzksnark_pp>(example, test_serialization);
    EXPECT_TRUE(bit);
};

}
