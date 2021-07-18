find_package(fmt CONFIG REQUIRED)
find_package(xbyak CONFIG REQUIRED)

add_library(libserver
        STATIC

        osprey_server.cpp
        proof_systems/groth16_server.cpp
        aux_struct/Log.hpp
        aux_struct/string_helper.hpp
        proof_systems/tinyram_circuit.hpp
        proof_systems/tinyram_r1cs_pp.hpp
        proof_systems/r1cs_adapter.hpp
        ram_compiler/tinyram_precompiler.cpp
        ram_compiler/tinyram_compiler_server.hpp
        ram_compiler/specialization_pool.hpp
        aux_struct/params_config.cpp)
add_subdirectory(analysis_program)
add_subdirectory(smart_contract)

target_link_libraries(libserver fmt)
message(“${fmt_INCLUDE_DIR}”)
target_link_libraries(libserver
        tinyram_snark
        smart_contract
        libanalysis
        ${Boost_LIBRARIES}
)

# Tests
#Integration Testing


#module testing

add_executable(
        params_config_tests
        aux_struct/tests/params_config_tests.cpp)
target_link_libraries(params_config_tests libserver)


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
add_test(NAME groth16_server_tests COMMAND groth16_server_tests)
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
add_dependencies(check groth16_server_tests)
#add_dependencies(check params_config_tests)