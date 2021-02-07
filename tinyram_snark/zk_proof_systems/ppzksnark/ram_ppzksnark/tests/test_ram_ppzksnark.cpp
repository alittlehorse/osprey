/**
 *****************************************************************************
 * @author     This file is part of tinyram_snark, developed by SCIPR Lab
 *             and contributors (see AUTHORS).
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <libff/common/profiling.hpp>

#include <tinyram_snark/common/default_types/ram_ppzksnark_pp.hpp>
#include <tinyram_snark/relations/ram_computations/rams/examples/ram_examples.hpp>
#include <tinyram_snark/zk_proof_systems/ppzksnark/ram_ppzksnark/examples/run_ram_ppzksnark.hpp>

using namespace tinyram_snark;

#ifndef NDEBUG

template<typename ppT>
void test_ram_ppzksnark(const size_t w,
                        const size_t k,
                        const size_t program_size,
                        const size_t input_size,
                        const size_t time_bound)
{
    libff::print_header("(enter) Test RAM ppzkSNARK");

    typedef ram_ppzksnark_machine_pp<ppT> machine_ppT;
    const size_t boot_trace_size_bound = program_size + input_size;
    const bool satisfiable = true;

    const ram_ppzksnark_architecture_params<ppT> ap(w, k);
    const ram_example<machine_ppT> example = gen_ram_example_complex<machine_ppT>(ap, boot_trace_size_bound, time_bound, satisfiable);

    const bool test_serialization = true;
    const bool bit = run_ram_ppzksnark<ppT>(example, test_serialization);
    assert(bit);

    libff::print_header("(leave) Test RAM ppzkSNARK");
}

int main()
{
    ram_ppzksnark_snark_pp<default_ram_ppzksnark_pp>::init_public_params();
    libff::start_profiling();

    const size_t program_size = 100;
    const size_t input_size = 2;
    const size_t time_bound = 20;

    // 16-bit TinyRAM with 16 registers
    test_ram_ppzksnark<default_ram_ppzksnark_pp>(16, 16, program_size, input_size, time_bound);

    // 32-bit TinyRAM with 16 registers
    test_ram_ppzksnark<default_ram_ppzksnark_pp>(32, 16, program_size, input_size, time_bound);
}

#else // NDEBUG

int main()
{
    printf("All tests here depend on assert() which is disabled by -DNDEBUG. Please recompile and run again.\n");
}
#endif // NDEBUG
