/** @file
 *****************************************************************************
 * @author     This file is part of tinyram_snark, developed by SCIPR Lab
 *             and contributors (see AUTHORS).
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/

#ifndef GADGET_TCC_
#define GADGET_TCC_

namespace tinyram_snark {

template<typename FieldT>
gadget<FieldT>::gadget(protoboard<FieldT> &pb, const std::string &annotation_prefix) :
    pb(pb), annotation_prefix(annotation_prefix)
{
#ifdef DEBUG
    assert(annotation_prefix != "");
#endif
}

} // tinyram_snark
#endif // GADGET_TCC_
