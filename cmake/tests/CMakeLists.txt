add_test(NAME iec2c.version COMMAND iec2c -v)
add_test(NAME iec2iec.version COMMAND iec2iec -v)
add_test(NAME iec2c.help COMMAND iec2c -h)
add_test(NAME iec2iec.help COMMAND iec2iec -h)

set(MATIEC_TEST_C_COMPILER "" CACHE FILEPATH
    "GCC/Clang-compatible C compiler used to validate generated PLC C code")
if(NOT MATIEC_TEST_C_COMPILER AND NOT MSVC)
    set(MATIEC_TEST_C_COMPILER "${CMAKE_C_COMPILER}")
endif()
if(NOT MATIEC_TEST_C_COMPILER)
    message(STATUS "Generated C syntax checks disabled; set MATIEC_TEST_C_COMPILER to GCC or Clang to enable them")
endif()

file(GLOB initialization_tests CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/tests/initialization/ok_*.st"
    "${PROJECT_SOURCE_DIR}/tests/initialization/bad_*.st")
list(APPEND initialization_tests "${CMAKE_CURRENT_SOURCE_DIR}/fixtures/real_precision.st")
foreach(input IN LISTS initialization_tests)
    get_filename_component(name "${input}" NAME_WE)
    add_test(NAME "initialization.${name}"
        COMMAND "${CMAKE_COMMAND}"
            "-DCOMPILER=$<TARGET_FILE:iec2c>"
            "-DINPUT=${input}"
            "-DOUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR}/${name}"
            "-DLIBRARY_DIR=${PROJECT_SOURCE_DIR}/lib"
            "-DC_COMPILER=${MATIEC_TEST_C_COMPILER}"
            "-DTEST_NAME=${name}"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/run_initialization.cmake")
endforeach()

add_test(NAME iec2iec.roundtrip
    COMMAND "${CMAKE_COMMAND}"
        "-DCOMPILER=$<TARGET_FILE:iec2iec>"
        "-DINPUT=${PROJECT_SOURCE_DIR}/tests/initialization/ok_array_scalar.st"
        "-DOUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR}/roundtrip"
        "-DLIBRARY_DIR=${PROJECT_SOURCE_DIR}/lib"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/run_roundtrip.cmake")

add_test(NAME install.relocation
    COMMAND "${CMAKE_COMMAND}"
        "-DBUILD_DIR=${PROJECT_BINARY_DIR}"
        "-DCONFIG=$<CONFIG>"
        "-DBIN_DIR=${CMAKE_INSTALL_BINDIR}"
        "-DDATA_DIR=${CMAKE_INSTALL_DATADIR}"
        "-DEXE_SUFFIX=${CMAKE_EXECUTABLE_SUFFIX}"
        "-DINPUT=${PROJECT_SOURCE_DIR}/tests/initialization/ok_array_scalar.st"
        "-DOUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR}/install test"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/run_install.cmake")

add_test(NAME cli.arguments
    COMMAND "${CMAKE_COMMAND}"
        "-DCOMPILER=$<TARGET_FILE:iec2c>"
        "-DINPUT=${PROJECT_SOURCE_DIR}/tests/initialization/ok_array_scalar.st"
        "-DLIBRARY_DIR=${PROJECT_SOURCE_DIR}/lib"
        "-DOUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR}/cli test"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/run_cli.cmake")
