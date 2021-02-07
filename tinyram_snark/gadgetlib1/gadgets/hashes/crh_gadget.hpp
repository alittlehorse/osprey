/**
 *****************************************************************************
 * @author     This file is part of tinyram_snark, developed by SCIPR Lab
 *             and contributors (see AUTHORS).
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/
#ifndef CRH_GADGET_HPP_
#define CRH_GADGET_HPP_

#include <tinyram_snark/gadgetlib1/gadgets/hashes/knapsack/knapsack_gadget.hpp>

namespace tinyram_snark {

// for now all CRH gadgets are knapsack CRH's; can be easily extended
// later to more expressive selector types.
template<typename FieldT>
using CRH_with_field_out_gadget = knapsack_CRH_with_field_out_gadget<FieldT>;

template<typename FieldT>
using CRH_with_bit_out_gadget = knapsack_CRH_with_bit_out_gadget<FieldT>;

} // tinyram_snark

#endif // CRH_GADGET_HPP_
