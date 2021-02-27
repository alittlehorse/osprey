set(SNARK_EXTRALIBS)
if(${CURVE} STREQUAL "BN128")
    set(
            SNARK_EXTRALIBS

            ${SNARK_EXTRALIBS}
            ${PROCPS_LIBRARIES}
            zm
    )
endif()

FIND_PACKAGE( Boost 1.56 COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_library(
        tinyram_snark
        STATIC

        common/data_structures/integer_permutation.cpp
        common/data_structures/set_commitment.cpp
        common/default_types/tinyram_ppzksnark_pp.cpp
        common/routing_algorithms/as_waksman_routing_algorithm.cpp
        common/routing_algorithms/benes_routing_algorithm.cpp
        gadgetlib1/constraint_profiling.cpp
        gadgetlib2/adapters.cpp
        gadgetlib2/constraint.cpp
        gadgetlib2/gadget.cpp
        gadgetlib2/infrastructure.cpp
        gadgetlib2/integration.cpp
        gadgetlib2/pp.cpp
        gadgetlib2/protoboard.cpp
        gadgetlib2/variable.cpp
        relations/ram_computations/memory/memory_store_trace.cpp
        relations/ram_computations/memory/ra_memory.cpp
        relations/ram_computations/rams/fooram/fooram_aux.cpp
        relations/ram_computations/rams/tinyram/tinyram_aux.cpp
)

target_link_libraries(
        tinyram_snark

        ff
        ${GMP_LIBRARIES}
        ${GMPXX_LIBRARIES}
        ${CRYPTO_LIBRARIES}
        ${PROCPS_LIBRARIES}
        ${SNARK_EXTRALIBS}
)
target_include_directories(
        tinyram_snark

        PUBLIC
        ${DEPENDS_DIR}/libff
        ${DEPENDS_DIR}/libfqfft
)
