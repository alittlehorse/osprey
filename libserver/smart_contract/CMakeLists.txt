cmake_minimum_required(VERSION 3.17)
project(EXAMPLEMAIN)
set(SRC_LIST example_main.cpp connectEthereum.cpp)
add_executable(example_main ${SRC_LIST})
include_directories("/usr/include/python3.8")
target_link_libraries(example_main "/usr/lib/x86_64-linux-gnu/libpython3.8.so") 

