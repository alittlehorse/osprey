add_library(libserver
        STATIC

        #ram_compiler/tinyram_compiler_server.hpp
        #proof_systems/ram_ppsnark_server.cpp
        proof_systems/groth16_server.cpp
        aux_struct/proof_params_config.cpp
        aux_struct/Log.hpp
        aux_struct/string_helper.hpp
        proof_systems/tinyram_circuit.hpp
        proof_systems/tinyram_r1cs_pp.hpp
        proof_systems/r1cs_adapter.hpp
        ram_compiler/tinyram_precompiler.cpp
        ram_compiler/tinyram_compiler_server.hpp
        ram_compiler/specialization_pool.hpp
        analysis_program/analysis_program.cpp
        aux_struct/params_config.cpp)

add_subdirectory(smart_contract)
target_link_libraries(libserver
        tinyram_snark
        fmt::fmt
        smart_contract
        ${Boost_LIBRARIES}
)

# Tests
#Integration Testing
add_executable(
        simulate
        simulate.cpp
        osprey_server.cpp)
target_link_libraries(simulate libserver)

#module testing

add_executable(analysis_program_tests
        analysis_program/tests/analysis_program_tests.cpp)
target_link_libraries(analysis_program_tests
        libserver)

add_executable(
        params_config_tests
        aux_struct/tests/params_config_tests.cpp)
target_link_libraries(params_config_tests libserver)

add_executable(
        log_tests
        EXCLUDE_FROM_ALL
        aux_struct/tests/log_tests.cpp)
target_link_libraries(log_tests fmt::fmt)

add_executable(
        ram_ppsnark_server_test
        EXCLUDE_FROM_ALL
        proof_systems/tests/ram_ppsnark_server_test.cpp
)
target_link_libraries(ram_ppsnark_server_test libserver)

add_executable(
        tinyram_precompiler_server_test
        EXCLUDE_FROM_ALL
        ram_compiler/tests/tinyram_precompiler_tests.cpp
)
target_link_libraries(tinyram_precompiler_server_test libserver)

add_executable(
        groth16_server_tests
        EXCLUDE_FROM_ALL
        proof_systems/tests/groth16_server_tests.cpp
)
target_link_libraries(groth16_server_tests libserver)

add_executable(
        tinyram_circuit_server_tests
        EXCLUDE_FROM_ALL
        proof_systems/tests/tinyram_circuit_server_tests.cpp
)
target_link_libraries(tinyram_circuit_server_tests libserver)

add_executable(
        r1cs_adapter_tests
        EXCLUDE_FROM_ALL
        proof_systems/tests/r1cs_adapter_tests.cpp
)
target_link_libraries(r1cs_adapter_tests libserver)

add_executable(
        compiler_tests
        EXCLUDE_FROM_ALL
        ram_compiler/tests/compiler_tests.cpp
)
target_link_libraries(compiler_tests libserver)


add_executable(
        server_provider
        EXCLUDE_FROM_ALL
        osprey_server.cpp)
target_link_libraries(server_provider libserver)


add_executable(
        specialization_pool_tests
        EXCLUDE_FROM_ALL
        ram_compiler/tests/specialization_pool_tests.cpp
)
target_link_libraries(specialization_pool_tests libserver)

#include(CTest)
#enable_testing()
#add_test(NAME groth16_server_tests COMMAND groth16_server_tests)
add_test(NAME simulate COMMAND simulate)
#add_test(NAME params_config_tests COMMAND params_config_tests)
#add_test(NAME proof_program_tests COMMAND proof_program_tests)
#add_test(NAME log_tests COMMAND log_tests)
#add_test(NAME ram_ppsnark_server_test COMMAND ram_ppsnark_server_test)
#add_test(NAME tinyram_compiler_server_test COMMAND tinyram_compiler_server_test)
#add_test(NAME tinyram_circuit_server_tests COMMAND tinyram_circuit_server_tests)
#add_test(NAME network_server_tests COMMAND string_helper_tests)
#add_test(NAME compiler_tests COMMAND compiler_tests)
#add_test(NAME specialization_pool_tests COMMAND specialization_pool_tests)

#add_dependencies(check proof_program_tests)
#add_dependencies(check log_tests)
#add_dependencies(check ram_ppsnark_server_test)
#add_dependencies(check tinyram_compiler_server_test)
#add_dependencies(check groth16_server_tests)
add_dependencies(check simulate)
#add_dependencies(check params_config_tests)