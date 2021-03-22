#include <libserver/ram_compiler/tinyram_compiler_server.hpp>
#include <libserver/proof_systems/tinyram_circuit.hpp>
#include <libserver/aux/proof_params_config.hpp>
#include <tinyram_snark/common/default_types/r1cs_gg_ppzksnark_pp.hpp>

using namespace libserver;
using namespace tinyram_snark;
int main(){
    typedef tinyram_r1cs_pp<default_r1cs_gg_ppzksnark_pp> tinyram_r1cs_params;
    proof_params_config p("avarage");

    tinyram_circuit<tinyram_r1cs_params> _tinyram_ciruit(p.get_processed_assembly_path(),p.get_computation_bounds_path(),p.get_architecture_params_path(),p.get_primary_input_path(),p.get_auxiliary_input_path());
    auto ap = _tinyram_ciruit.get_ram_architecture_params();
    auto bounds = _tinyram_ciruit.get_bounds();

    size_t tinyram_input_size_bound, tinyram_program_size_bound, time_bound;
    tinyram_input_size_bound = bounds["tinyram_input_size_bound"];
    tinyram_program_size_bound = bounds["tinyram_program_size_bound"];
    time_bound = bounds["time_bound"];

    auto program = _tinyram_ciruit.get_tinyram_program();
    auto boot_trace = _tinyram_ciruit.get_boot_trace();
    const size_t boot_trace_size_bound = tinyram_input_size_bound + tinyram_program_size_bound;
    tinyram_compiler_server<tinyram_r1cs_params> compiler(p.get_log_path());
    compiler.specialization(ap,boot_trace_size_bound,time_bound);
    auto cs = compiler.compile_r1cs_constrain_system();
    assert(cs->auxiliary_input_size>0);
    auto primary_input = compiler.compile_r1cs_primary_input(ap,boot_trace_size_bound,boot_trace);
    assert(primary_input!=std::nullopt);
    auto auxiliary_input = compiler.compile_r1cs_auxiliary_input(boot_trace,_tinyram_ciruit.get_auxiliary_input_tap());
    assert(auxiliary_input!=std::nullopt);
    assert(cs->is_satisfied(primary_input.value(),auxiliary_input.value()));
    return 0;
}

