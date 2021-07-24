find_package(PythonLibs REQUIRED)
add_library(libanalysis

        STATIC
        analysis_program.cpp
        analysis_program.hpp
        analysis_err_code.hpp)
target_include_directories(libanalysis PUBLIC ${PYTHON_INCLUDE_DIRS})
target_link_libraries(libanalysis ${PYTHON_LIBRARIES})