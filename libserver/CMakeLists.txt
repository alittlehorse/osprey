
add_library(libserver
        STATIC

        ram_ppsnark_server.cpp
        proof_program.cpp
        Log.hpp
        tinyram_complier_server.hpp
        )
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

        tests/log_tests.cpp
)
target_link_libraries(proof_program_tests libserver)

add_executable(
        ram_ppsnark_server_test

        tests/ram_ppsnark_server_test.cpp
)
target_link_libraries(ram_ppsnark_server_test libserver)

include(CTest)
enable_testing()
add_test(
        NAME proof_program_tests
        COMMAND proof_program_tests
)
add_test(
        NAME log_tests
        COMMAND log_tests
)
add_test(
        NAME ram_ppsnark_server_test
        COMMAND ram_ppsnark_server_test
)
add_dependencies(check proof_program_tests)
add_dependencies(check log_tests)
add_dependencies(check ram_ppsnark_server_test)