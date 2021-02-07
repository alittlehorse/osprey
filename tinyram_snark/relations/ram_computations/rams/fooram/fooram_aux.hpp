/** @file
 *****************************************************************************

 Declaration of auxiliary functions for FOORAM.

 *****************************************************************************
 * @author     This file is part of tinyram_snark, developed by SCIPR Lab
 *             and contributors (see AUTHORS).
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/

#ifndef FOORAM_AUX_HPP_
#define FOORAM_AUX_HPP_

#include <iostream>
#include <vector>

#include <libff/common/utils.hpp>

#include <tinyram_snark/relations/ram_computations/memory/memory_interface.hpp>
#include <tinyram_snark/relations/ram_computations/memory/memory_store_trace.hpp>

namespace tinyram_snark {

typedef std::vector<size_t> fooram_program;
typedef std::vector<size_t> fooram_input_tape;
typedef typename std::vector<size_t>::const_iterator fooram_input_tape_iterator;

class fooram_architecture_params {
public:
    size_t w;
    fooram_architecture_params(const size_t w=16);

    size_t num_addresses() const;
    size_t address_size() const;
    size_t value_size() const;
    size_t cpu_state_size() const;
    size_t initial_pc_addr() const;

    memory_contents initial_memory_contents(const fooram_program &program,
                                            const fooram_input_tape &primary_input) const;

    libff::bit_vector initial_cpu_state(const fooram_input_tape &primary_input) const;
    fooram_input_tape primary_input_from_boot_trace(const memory_store_trace &boot_trace) const;

    void print() const;
    bool operator==(const fooram_architecture_params &other) const;

    friend std::ostream& operator<<(std::ostream &out, const fooram_architecture_params &ap);
    friend std::istream& operator>>(std::istream &in, fooram_architecture_params &ap);
};

} // tinyram_snark

#endif // FOORAM_AUX_HPP_
