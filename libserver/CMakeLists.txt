include(FindPkgConfig)
pkg_check_modules(LIBEVENT REQUIRED libevent>2.1.10)
add_library(libserver
        STATIC

        ram_complier/tinyram_complier_server.tcc
        proof_systems/ram_ppsnark_server.cpp
        proof_systems/groth16_server.hpp
        aux/proof_program.cpp
        aux/Log.hpp
        aux/string_helper.hpp
        proof_systems/groth16_server.hpp
        )

add_subdirectory(smart_contract)
target_link_libraries(libserver
        tinyram_snark
)


# Tests
add_executable(
        proof_program_tests

        tests/proof_program_tests.cpp)
target_link_libraries(proof_program_tests libserver)

add_executable(
        log_tests

        tests/log_tests.cpp)
target_link_libraries(log_tests libserver)

add_executable(
        ram_ppsnark_server_test

        tests/ram_ppsnark_server_test.cpp
)
target_link_libraries(ram_ppsnark_server_test libserver)

add_executable(
        tinyram_complier_server_test

        tests/tinyram_complier_server_test.cpp
)
target_link_libraries(tinyram_complier_server_test libserver)
add_executable(
        string_helper_tests

        tests/string_helper_tests.cpp
)
target_link_libraries(string_helper_tests libserver)

add_executable(
        network_server_tests

        tests/network_test.cpp
)
target_link_libraries(network_server_tests ${LIBEVENT_LIBRARIES})
target_link_libraries(network_server_tests libserver)

add_executable(
        groth16_server_tests

        tests/groth16_server_tests.cpp
)
target_link_libraries(groth16_server_tests libserver)

include(CTest)
enable_testing()
add_test(NAME proof_program_tests COMMAND proof_program_tests)
add_test(NAME log_tests COMMAND log_tests)
add_test(NAME ram_ppsnark_server_test COMMAND ram_ppsnark_server_test)
add_test(NAME tinyram_complier_server_test COMMAND tinyram_complier_server_test)

add_test(NAME string_helper_tests COMMAND string_helper_tests)
add_test(NAME groth16_server_tests COMMAND groth16_server_tests)

#add_test(NAME network_server_tests COMMAND string_helper_tests)

add_dependencies(check proof_program_tests)
add_dependencies(check log_tests)
add_dependencies(check ram_ppsnark_server_test)
add_dependencies(check tinyram_complier_server_test)
add_dependencies(check string_helper_tests)
add_dependencies(check groth16_server_tests)