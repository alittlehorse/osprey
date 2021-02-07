/** @file
 *****************************************************************************
 * @author     This file is part of tinyram_snark, developed by SCIPR Lab
 *             and contributors (see AUTHORS).
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/

#ifndef GADGET_HPP_
#define GADGET_HPP_

#include <tinyram_snark/gadgetlib1/protoboard.hpp>

namespace tinyram_snark {

template<typename FieldT>
class gadget {
protected:
    protoboard<FieldT> &pb;
    const std::string annotation_prefix;
public:
    gadget(protoboard<FieldT> &pb, const std::string &annotation_prefix="");
};

} // tinyram_snark
#include <tinyram_snark/gadgetlib1/gadget.tcc>

#endif // GADGET_HPP_
