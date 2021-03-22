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

#ifndef OSPREY_SPECIALIZATION_POOL_H
#define OSPREY_SPECIALIZATION_POOL_H
#include <unordered_map>
#include <optional>
#include <tinyram_snark/relations/ram_computations/rams/ram_params.hpp>
#include <tinyram_snark/relations/ram_computations/rams/tinyram/tinyram_params.hpp>
#include <tinyram_snark/reductions/ram_to_r1cs/ram_to_r1cs.hpp>


namespace libserver{

    class specialization_factor{
    public:
    private:
        tinyram_snark::tinyram_architecture_params ap;
        size_t boot_trace_size_bound;
        size_t time_bound;
    public:
        specialization_factor(const tinyram_snark::tinyram_architecture_params &ap,const size_t boot_trace_size_bound,const size_t time_bound):
                ap(ap),boot_trace_size_bound(boot_trace_size_bound),time_bound(time_bound){}
        specialization_factor()=default;
        bool operator==(const specialization_factor &other) const{
            if(this->time_bound == other.time_bound
               && this->boot_trace_size_bound==other.boot_trace_size_bound
               && this->ap==other.ap)
                return true;
            else return false;
        }

        [[nodiscard]] const tinyram_snark::tinyram_architecture_params& get_ram_architecture_params() const{
            return ap;
        };
        const size_t get_boot_trace_size_bound() const{
            return boot_trace_size_bound;
        }
        const size_t get_time_bound() const{
            return time_bound;
        }
        struct KeyHasher
        {
            size_t operator()(const specialization_factor& k) const
            {
                return (std::hash<size_t>()(k.get_ram_architecture_params().k)<< 1)
                       ^(std::hash<size_t>()(k.get_ram_architecture_params().w)<< 1)
                       ^ (std::hash<size_t>()(k.get_boot_trace_size_bound()) << 1)
                       ^ (std::hash<size_t>()(k.get_boot_trace_size_bound()) << 1);
            }
        };
    };




    template<typename ramT>
    class specialization_pool{
    private:
        static std::unordered_map<specialization_factor,tinyram_snark::ram_to_r1cs<ramT>*,specialization_factor::KeyHasher> pool;
    public:
        static std::optional<tinyram_snark::ram_to_r1cs<ramT>*>
        get_r1cs_constraint_system(const specialization_factor&);
        static bool push_r1cs_constraint_system_into_pool(const specialization_factor&,tinyram_snark::ram_to_r1cs<ramT>*);
        static bool has_contained(const specialization_factor&);
        static bool empty();
        static size_t size();
    };

}


#include <libserver/ram_compiler/specialization_pool.tcc>
#endif //OSPREY_SPECIALIZATION_POOL_H
