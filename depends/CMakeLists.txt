if(${CURVE} STREQUAL "BN128")
  include_directories(ate-pairing/include)
  add_library(
    zm
    STATIC

    ate-pairing/src/zm.cpp
    ate-pairing/src/zm2.cpp
  )

endif()

if(NOT "${USE_LINKED_LIBRARIES}")
  OPTION(IS_LIBFF_PARENT OFF)
  add_subdirectory(libff)

  OPTION(IS_LIBFQFFT_PARENT OFF)
  add_subdirectory(libfqfft)
endif()