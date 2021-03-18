/** @file
 *****************************************************************************

 Declaration of interfaces for r1cs_constrain_system_pool

circuit generator is universal: when given input bounds l, n, T, it produces a circuit that can verify
the execution of any program with ≤ l instructions, on any input of size ≤ n, for ≤ T steps.

 it means circuit can be multiplexed, if l,n,T is same;

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/
#ifndef OSPREY_R1CS_CONSTRAINT_SYSTEM_POOL_HPP
#define OSPREY_R1CS_CONSTRAINT_SYSTEM_POOL_HPP
#include <unordered_map>
#include <tinyram_snark/relations/constraint_satisfaction_problems/r1cs/r1cs.hpp>
#include <libserver/ram_complier/tinyram_complier_server.hpp>
namespace libserver{
    template <typename ppT>
    class r1cs_constraint_system_pool {
    private:
        static std::unordered_map<std::pair<int,int>,tinyram_snark::r1cs_constraint_system<libff::Fr<ppT>>> pool;

    public :
        static tinyram_snark::r1cs_constraint_system<libff::Fr<ppT>> get_r1cs_constrain_system(const std::pair<int,int>& key);
    };

    template<typename ppT>
    tinyram_snark::r1cs_constraint_system<libff::Fr<ppT>>
    r1cs_constraint_system_pool<libff::Fr<ppT>>::get_r1cs_constrain_system(const std::pair<int, int>& key) {
        if(auto it = pool.find(key);it!=pool.end()){
            return it->second;
        }
        else{
            tinyram_complier_server complier;
            auto cs = complier.complie_r1cs<ppT>();
            pool[key] = cs;
            return cs;
        }
    }

}


#endif //OSPREY_R1CS_CONSTRAINT_SYSTEM_POOL_HPP
