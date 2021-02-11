
add_library(libserver
        STATIC

        construct_proof.cpp
        proof_program.cpp
        Log.hpp
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
add_dependencies(check proof_program_tests)
add_dependencies(check log_tests)