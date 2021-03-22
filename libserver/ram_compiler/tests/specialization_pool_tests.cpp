
#include <libserver/ram_compiler/specialization_pool.hpp>
#include <tinyram_snark/relations/ram_computations/rams/tinyram/tinyram_params.hpp>
#include <libff/common/default_types/ec_pp.hpp>
#include <cassert>
using namespace libserver;
using namespace tinyram_snark;


int main(){
    tinyram_architecture_params ap(16,16);
    //typedef libff::Fr<libff::default_ec_pp> FieldT;
    //typedef tinyram_r1cs_pp<default_r1cs_gg_ppzksnark_pp>::machine_pp m;
    specialization_factor sf(ap,64,20);
    tinyram_architecture_params ap2(16,16);
    specialization_factor sf1(ap2,64,21);
    //assert(sf == sf1);
    assert(specialization_pool<ram_tinyram<libff::default_ec_pp>>::empty()==true);
    tinyram_snark::ram_to_r1cs<ram_tinyram<libff::default_ec_pp>>* a = nullptr;
    tinyram_snark::ram_to_r1cs<ram_tinyram<libff::default_ec_pp>>* b = (tinyram_snark::ram_to_r1cs<ram_tinyram<libff::default_ec_pp>>*)(void*)0;
    specialization_pool<ram_tinyram<libff::default_ec_pp>>::push_r1cs_constraint_system_into_pool(sf,a);
    specialization_pool<ram_tinyram<libff::default_ec_pp>>::push_r1cs_constraint_system_into_pool(sf1,b);

    assert(specialization_pool<ram_tinyram<libff::default_ec_pp>>::size()==2);
    auto s = specialization_pool<ram_tinyram<libff::default_ec_pp>>::get_r1cs_constraint_system(sf1);
    return 0;
}


