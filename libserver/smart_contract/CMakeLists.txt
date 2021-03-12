cmake_minimum_required(VERSION 3.17)
add_library(smart_contract
        connectEthereum.cpp)
include_directories("/usr/include/python3.8")
target_link_libraries(smart_contract "/usr/lib/x86_64-linux-gnu/libpython3.8.so")

#tests
add_executable(contract_tests contract_tests.cpp)
target_link_libraries(contract_tests smart_contract)


#add_test(NAME contract_tests COMMAND contract_tests)

#add_dependencies(check contract_tests)
