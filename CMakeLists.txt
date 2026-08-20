cmake_minimum_required(VERSION 3.16)

project(matiec VERSION 0.1 LANGUAGES C CXX)

include(GNUInstallDirs)

find_package(BISON 2.4 REQUIRED)
find_package(FLEX REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(MATIEC_WARNING_OPTIONS
    -Wall
    -Wpointer-arith
    -Wwrite-strings
    -Wno-unused
    -Wno-overloaded-virtual)

set(MATIEC_LIBDIR "${CMAKE_INSTALL_FULL_DATADIR}/matiec/lib"
    CACHE PATH "Directory containing the matiec IEC standard library")

execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    OUTPUT_VARIABLE MATIEC_REVISION
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/config/config.h")

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/stage1_2")

BISON_TARGET(
    iec_parser
    "${CMAKE_CURRENT_SOURCE_DIR}/stage1_2/iec_bison.yy"
    "${CMAKE_CURRENT_BINARY_DIR}/stage1_2/iec_bison.cc"
    DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/stage1_2/iec_bison.hh"
    COMPILE_FLAGS "-Wno-yacc")

FLEX_TARGET(
    iec_scanner
    "${CMAKE_CURRENT_SOURCE_DIR}/stage1_2/iec_flex.ll"
    "${CMAKE_CURRENT_BINARY_DIR}/stage1_2/iec_flex.cc"
    COMPILE_FLAGS "--warn")

ADD_FLEX_BISON_DEPENDENCY(iec_scanner iec_parser)

add_library(absyntax STATIC
    absyntax/absyntax.cc
    absyntax/visitor.cc)

add_library(absyntax_utils STATIC
    absyntax_utils/absyntax_utils.cc
    absyntax_utils/add_en_eno_param_decl.cc
    absyntax_utils/decompose_var_instance_name.cc
    absyntax_utils/array_dimension_iterator.cc
    absyntax_utils/case_element_iterator.cc
    absyntax_utils/function_call_iterator.cc
    absyntax_utils/function_call_param_iterator.cc
    absyntax_utils/function_param_iterator.cc
    absyntax_utils/get_sizeof_datatype.cc
    absyntax_utils/get_var_name.cc
    absyntax_utils/search_il_label.cc
    absyntax_utils/search_base_type.cc
    absyntax_utils/search_fb_instance_decl.cc
    absyntax_utils/search_fb_typedecl.cc
    absyntax_utils/search_varfb_instance_type.cc
    absyntax_utils/search_var_instance_decl.cc
    absyntax_utils/spec_init_separator.cc
    absyntax_utils/type_initial_value.cc
    absyntax_utils/debug_ast.cc
    absyntax_utils/get_datatype_info.cc)

add_library(stage1_2 STATIC
    ${BISON_iec_parser_OUTPUTS}
    ${FLEX_iec_scanner_OUTPUTS}
    stage1_2/create_enumtype_conversion_functions.cc
    stage1_2/stage1_2.cc)

target_include_directories(stage1_2 PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/absyntax"
    "${CMAKE_CURRENT_SOURCE_DIR}/stage1_2"
    "${CMAKE_CURRENT_BINARY_DIR}/stage1_2")
target_compile_definitions(stage1_2 PRIVATE
    DEFAULT_LIBDIR="${MATIEC_LIBDIR}"
    YY_BUF_SIZE=65536)
target_compile_options(stage1_2 PRIVATE -fpermissive)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(stage1_2 PRIVATE -Wno-free-nonheap-object)
endif()

add_library(stage3 STATIC
    stage3/stage3.cc
    stage3/flow_control_analysis.cc
    stage3/fill_candidate_datatypes.cc
    stage3/narrow_candidate_datatypes.cc
    stage3/forced_narrow_candidate_datatypes.cc
    stage3/print_datatypes_error.cc
    stage3/datatype_functions.cc
    stage3/lvalue_check.cc
    stage3/array_range_check.cc
    stage3/case_elements_check.cc
    stage3/constant_folding.cc
    stage3/declaration_check.cc
    stage3/enum_declaration_check.cc
    stage3/remove_forward_dependencies.cc)

add_library(stage4_c STATIC
    stage4/stage4.cc
    stage4/generate_c/generate_c.cc)
target_include_directories(stage4_c PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/absyntax")

add_library(stage4_iec STATIC
    stage4/stage4.cc
    stage4/generate_iec/generate_iec.cc)
target_include_directories(stage4_iec PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/absyntax")

foreach(target absyntax absyntax_utils stage1_2 stage3 stage4_c stage4_iec)
    target_compile_options(${target} PRIVATE ${MATIEC_WARNING_OPTIONS})
    target_include_directories(${target} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_BINARY_DIR}")
endforeach()

add_executable(iec2c main.cc)
target_link_libraries(iec2c PRIVATE
    stage1_2 stage3 stage4_c absyntax absyntax_utils)

add_executable(iec2iec main.cc)
target_link_libraries(iec2iec PRIVATE
    stage1_2 stage3 stage4_iec absyntax absyntax_utils)

foreach(target iec2c iec2iec)
    target_compile_options(${target} PRIVATE ${MATIEC_WARNING_OPTIONS})
    target_compile_definitions(${target} PRIVATE HGVERSION="${MATIEC_REVISION}")
    target_include_directories(${target} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_BINARY_DIR}")
endforeach()

install(TARGETS iec2c iec2iec
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
install(TARGETS absyntax absyntax_utils stage1_2 stage3 stage4_c stage4_iec
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/matiec/lib")
