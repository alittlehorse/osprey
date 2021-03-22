/** @file
 *****************************************************************************

 Declaration of interfaces for r1cs_constrain_system_pool

circuit generator is universal: when given input bounds l, n, T, it produces a circuit that can verify
the execution of any program with ≤ l instructions, on any input of size ≤ n, for ≤ T steps.

 it means circuit can be multiplexed, if l,n,T,w,k are same;

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/


#include "specialization_pool.hpp"

namespace libserver{

    template<typename ramT>
    std::unordered_map<specialization_factor,tinyram_snark::ram_to_r1cs<ramT>*,specialization_factor::KeyHasher>
            specialization_pool<ramT>::pool = {};

    template<typename ramT>
    bool specialization_pool<ramT>::push_r1cs_constraint_system_into_pool(const specialization_factor& key,tinyram_snark::ram_to_r1cs<ramT>* r2r) {
        if(has_contained(key))return true;
        try{
            pool[key] = r2r;
        }
        catch (std::exception &e){
            return false;
        }
        return true;
    }

    template<typename ramT>
    bool specialization_pool<ramT>::has_contained(const specialization_factor& key) {
        if(pool.contains(key))return true;
        return false;
    }

    template<typename ramT>
     bool specialization_pool<ramT>::empty() {
        if(pool.empty())return true;
        else return false;
    }

    template<typename ramT>
    std::optional<tinyram_snark::ram_to_r1cs<ramT>*>
    specialization_pool<ramT>::get_r1cs_constraint_system(const specialization_factor& key){
        if(auto it = pool.find(key);it!=pool.end()){
            return {it->second};
        }
        else return std::nullopt;
    }

    template<typename ramT>
    size_t specialization_pool<ramT>::size() {
        return pool.size();
    }

}