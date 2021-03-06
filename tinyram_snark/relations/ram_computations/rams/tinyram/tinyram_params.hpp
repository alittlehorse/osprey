/** @file
 *****************************************************************************

 Declaration of public parameters for TinyRAM.

 *****************************************************************************
 * @author     This file is part of tinyram_snark, developed by SCIPR Lab
 *             and contributors (see AUTHORS).
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/

#ifndef TINYRAM_PARAMS_HPP_
#define TINYRAM_PARAMS_HPP_

#include <tinyram_snark/gadgetlib1/gadgets/cpu_checkers/tinyram/tinyram_cpu_checker.hpp>
#include <tinyram_snark/relations/ram_computations/rams/ram_params.hpp>
#include <tinyram_snark/relations/ram_computations/rams/tinyram/tinyram_aux.hpp>

namespace tinyram_snark {

template<typename FieldT>
class ram_tinyram {
public:
    static size_t timestamp_length;

    typedef FieldT base_field_type;
    typedef tinyram_protoboard<FieldT> protoboard_type;
    typedef tinyram_gadget<FieldT> gadget_base_type;
    typedef tinyram_cpu_checker<FieldT> cpu_checker_type;
    typedef tinyram_architecture_params architecture_params_type;
};

template<typename FieldT>
size_t ram_tinyram<FieldT>::timestamp_length = 300;

} // tinyram_snark

#endif // TINYRAM_PARAMS_HPP_
