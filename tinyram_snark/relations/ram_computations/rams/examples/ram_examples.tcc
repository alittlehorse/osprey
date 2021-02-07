/** @file
 *****************************************************************************

 Implementation of interfaces for a RAM example, as well as functions to sample
 RAM examples with prescribed parameters (according to some distribution).

 See ram_examples.hpp .

 *****************************************************************************
 * @author     This file is part of tinyram_snark, developed by SCIPR Lab
 *             and contributors (see AUTHORS).
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/

#ifndef RAM_EXAMPLES_TCC_
#define RAM_EXAMPLES_TCC_

#include <tinyram_snark/relations/ram_computations/rams/tinyram/tinyram_aux.hpp>

namespace tinyram_snark {

template<typename ramT>
ram_example<ramT> gen_ram_example_simple(const ram_architecture_params<ramT> &ap, const size_t boot_trace_size_bound, const size_t time_bound, const bool satisfiable)
{
    libff::enter_block("Call to gen_ram_example_simple");

    const size_t program_size = boot_trace_size_bound / 2;
    const size_t input_size = boot_trace_size_bound - program_size;

    ram_example<ramT> result;

    result.ap = ap;
    result.boot_trace_size_bound = boot_trace_size_bound;
    result.time_bound = time_bound;

    tinyram_program prelude; prelude.instructions = generate_tinyram_prelude(ap);

    size_t boot_pos = 0;
    for (size_t i = 0; i < prelude.instructions.size(); ++i)
    {
        result.boot_trace.set_trace_entry(boot_pos++, std::make_pair(i, prelude.instructions[i].as_dword(ap)));
    }

    result.boot_trace[boot_pos] = std::make_pair(boot_pos++, tinyram_instruction(tinyram_opcode_ANSWER, true,      0,       0,       satisfiable ? 0 : 1).as_dword(ap)); /* answer 0/1 depending on satisfiability */

    while (boot_pos < program_size)
    {
        result.boot_trace.set_trace_entry(boot_pos++, random_tinyram_instruction(ap).as_dword(ap));
    }

    for (size_t i = 0; i < input_size; ++i)
    {
        result.boot_trace.set_trace_entry(boot_pos++, std::make_pair((1ul<<(ap.dwaddr_len()-1)) + i, std::rand() % (1ul<<(2*ap.w))));
    }

    assert(boot_pos == boot_trace_size_bound);

    libff::leave_block("Call to gen_ram_example_simple");
    return result;
}

template<typename ramT>
ram_example<ramT> gen_ram_example_complex(const ram_architecture_params<ramT> &ap, const size_t boot_trace_size_bound, const size_t time_bound, const bool satisfiable)
{
    libff::enter_block("Call to gen_ram_example_complex");

    const size_t program_size = boot_trace_size_bound / 2;
    const size_t input_size = boot_trace_size_bound - program_size;

    assert(2*ap.w/8*program_size < 1ul<<(ap.w-1));
    assert(ap.w/8*input_size < 1ul<<(ap.w-1));
    assert(input_size >= 1);

    ram_example<ramT> result;

    result.ap = ap;
    result.boot_trace_size_bound = boot_trace_size_bound;
    result.time_bound = time_bound;

    tinyram_program prelude; prelude.instructions = generate_tinyram_prelude(ap);

    size_t boot_pos = boot_trace_size_bound-1;
    size_t code_pos = 0;
    for (size_t i = 0; i < prelude.instructions.size(); ++i)
    {
        result.boot_trace.set_trace_entry(boot_pos--, std::make_pair(code_pos++, prelude.instructions[i].as_dword(ap)));
    }

    const size_t prelude_len = prelude.instructions.size();
    const size_t instr_addr = (prelude_len+4)*(2*ap.w/8);

    const size_t primary_input_base_addr_in_bytes = 1ul << (ap.w - 1);
    const size_t increment = ap.w/8;

    const size_t input_addr = primary_input_base_addr_in_bytes + increment; // byte address of the first input word

    result.boot_trace.set_trace_entry(boot_pos--, std::make_pair(code_pos++, tinyram_instruction(tinyram_opcode_LOADB,  true,      1,       0, instr_addr).as_dword(ap)));
    result.boot_trace.set_trace_entry(boot_pos--, std::make_pair(code_pos++, tinyram_instruction(tinyram_opcode_LOADW,  true,      2,       0, input_addr).as_dword(ap)));
    result.boot_trace.set_trace_entry(boot_pos--, std::make_pair(code_pos++, tinyram_instruction(tinyram_opcode_SUB,    false,     1,       1, 2).as_dword(ap)));
    result.boot_trace.set_trace_entry(boot_pos--, std::make_pair(code_pos++, tinyram_instruction(tinyram_opcode_STOREB, true,      1,       0, instr_addr).as_dword(ap)));
    result.boot_trace.set_trace_entry(boot_pos--, std::make_pair(code_pos++, tinyram_instruction(tinyram_opcode_ANSWER, true,      0,       0, 1).as_dword(ap)));

    for (; code_pos < program_size; ++code_pos)
    {
        result.boot_trace.set_trace_entry(boot_pos--, std::make_pair(code_pos++, random_tinyram_instruction(ap).as_dword(ap)));
    }

    const size_t primary_input_base_addr_in_dwords = 1ul << (ap.dwaddr_len() - 1);

    const size_t first_dword = ((satisfiable ? 1ul : 0) <<ap.w) + (primary_input_base_addr_in_bytes + increment * input_size);
    result.boot_trace.set_trace_entry(boot_pos--, std::make_pair(primary_input_base_addr_in_dwords, first_dword));

    for (size_t i = 1; i < input_size; i += 2)
    {
        size_t dword = std::rand() % (1ul<<ap.w);
        if (i + 1 < input_size)
        {
            dword = (dword << ap.w) + (std::rand() % (1ul<<ap.w));
        }
        result.boot_trace.set_trace_entry(boot_pos--, std::make_pair(primary_input_base_addr_in_dwords + (i+1)/2, dword));
    }

    libff::leave_block("Call to gen_ram_example_complex");
    return result;
}

} // tinyram_snark

#endif // RAM_EXAMPLES_TCC_
