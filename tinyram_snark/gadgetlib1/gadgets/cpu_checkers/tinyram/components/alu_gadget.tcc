/** @file
 *****************************************************************************

 Implementation of interfaces for the TinyRAM ALU gadget.

 See alu.hpp .

 *****************************************************************************
 * @author     This file is part of tinyram_snark, developed by SCIPR Lab
 *             and contributors (see AUTHORS).
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/

#ifndef ALU_GADGET_TCC_
#define ALU_GADGET_TCC_

namespace tinyram_snark {

template<typename FieldT>
void ALU_gadget<FieldT>::generate_r1cs_constraints()
{
    for (size_t i = 0; i < 1ul<<this->pb.ap.opcode_width(); ++i)
    {
        if (components[i])
        {
            components[i]->generate_r1cs_constraints();
        }
    }
}

template<typename FieldT>
void ALU_gadget<FieldT>::generate_r1cs_witness()
{
    for (size_t i = 0; i < 1ul<<this->pb.ap.opcode_width(); ++i)
    {
        if (components[i])
        {
            components[i]->generate_r1cs_witness();
        }
    }
}

} // tinyram_snark

#endif // ALU_GADGET_TCC_
