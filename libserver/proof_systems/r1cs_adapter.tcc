//
// Created by alittlehorse on 3/18/21.
//

namespace libserver{

    template<typename tinyram_r1cs_params>
    using FieldT = typename tinyram_r1cs_params::FieldT;

    template<typename tinyram_r1cs_params>
    const r1cs_primary_input<typename tinyram_r1cs_params::FieldT> r1cs_adapter<tinyram_r1cs_params>::get_r1cs_primary_input() {
        return primary_input;
    }
    template<typename tinyram_r1cs_params>
    const r1cs_auxiliary_input<typename tinyram_r1cs_params::FieldT> r1cs_adapter<tinyram_r1cs_params>::get_auxiliary_input(){
        return auxiliary_input;
    }
    template<typename tinyram_r1cs_params>
    const r1cs_constraint_system<typename tinyram_r1cs_params::FieldT> r1cs_adapter<tinyram_r1cs_params>::get_r1cs_constraint_system()
    {
        return cs;
    }
}
