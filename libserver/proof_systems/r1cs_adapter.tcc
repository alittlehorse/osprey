/** @file
 *****************************************************************************

Declaration of interface of r1cs_adapter.
 r1cs_adapter translates three part:
 1. tinyram_circuit to r1cs constraint system
 2. tinyram_primary input to r1cs primary input
 3. tinyram aux_struct input to r1cs aux_struct input

 this interface is like a adapter for tinyram circuit and zk proof system use them.

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/
namespace libserver{

    template<typename tinyram_r1cs_params>
    using FieldT = typename tinyram_r1cs_params::FieldT;

    template<typename tinyram_r1cs_params>
    const r1cs_primary_input<typename tinyram_r1cs_params::FieldT> r1cs_adapter<tinyram_r1cs_params>::get_r1cs_primary_input() const{
        return primary_input;
    }
    template<typename tinyram_r1cs_params>
    const r1cs_auxiliary_input<typename tinyram_r1cs_params::FieldT> r1cs_adapter<tinyram_r1cs_params>::get_auxiliary_input() const{
        return auxiliary_input;
    }
    template<typename tinyram_r1cs_params>
    const r1cs_constraint_system<typename tinyram_r1cs_params::FieldT> r1cs_adapter<tinyram_r1cs_params>::get_r1cs_constraint_system()const
    {
        return cs;
    }
}
