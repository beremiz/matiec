cmake_minimum_required(VERSION 3.24)
project(matiec VERSION 0.1 LANGUAGES C CXX)

include(GNUInstallDirs)
include(CTest)

find_package(BISON 2.4 REQUIRED)
find_package(FLEX REQUIRED)

set(MATIEC_REVISION "" CACHE STRING "Revision displayed by iec2c/iec2iec -v")
if(NOT MATIEC_REVISION)
    find_package(Git QUIET)
    if(GIT_FOUND)
        execute_process(COMMAND "${GIT_EXECUTABLE}" rev-parse --short=12 HEAD
            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
            OUTPUT_VARIABLE MATIEC_REVISION OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET)
    endif()
    if(NOT MATIEC_REVISION)
        set(MATIEC_REVISION "unknown")
    endif()
endif()

set(MATIEC_INSTALL_LIBDIR "${CMAKE_INSTALL_FULL_DATADIR}/matiec/lib")
file(RELATIVE_PATH MATIEC_RELATIVE_LIBDIR "${CMAKE_INSTALL_FULL_BINDIR}"
    "${MATIEC_INSTALL_LIBDIR}")
configure_file(cmake/config.h.in generated/config/config.h @ONLY)

set(parser_dir "${CMAKE_CURRENT_BINARY_DIR}/generated/stage1_2")
file(MAKE_DIRECTORY "${parser_dir}")
BISON_TARGET(IECParser stage1_2/iec_bison.yy "${parser_dir}/iec_bison.cc"
    DEFINES_FILE "${parser_dir}/iec_bison.hh" COMPILE_FLAGS "-Wno-yacc")
FLEX_TARGET(IECLexer stage1_2/iec_flex.ll "${parser_dir}/iec_flex.cc"
    COMPILE_FLAGS "--warn --nounistd")
ADD_FLEX_BISON_DEPENDENCY(IECLexer IECParser)

# stage1_2.cc also includes the generated token header.
add_custom_target(matiec_parser DEPENDS ${BISON_IECParser_OUTPUTS})

add_library(matiec_options INTERFACE)
target_compile_features(matiec_options INTERFACE cxx_std_17)
target_include_directories(matiec_options INTERFACE
    "${CMAKE_CURRENT_BINARY_DIR}/generated"
    "${parser_dir}"
    "${CMAKE_CURRENT_SOURCE_DIR}/stage1_2")
target_compile_definitions(matiec_options INTERFACE
    MATIEC_CMAKE_BUILD HGVERSION="${MATIEC_REVISION}")
if(MSVC)
    target_compile_options(matiec_options INTERFACE /W3 /utf-8)
    target_compile_definitions(matiec_options INTERFACE
        _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_WARNINGS)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "^(GNU|Clang|AppleClang)$")
    target_compile_options(matiec_options INTERFACE
        -Wall -Wpointer-arith -Wwrite-strings -Wno-unused -Wno-overloaded-virtual)
endif()

add_library(matiec_frontend OBJECT
    absyntax/absyntax.cc
    absyntax/visitor.cc
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
    absyntax_utils/get_datatype_info.cc
    ${BISON_IECParser_OUTPUTS}
    ${FLEX_IECLexer_OUTPUTS}
    stage1_2/create_enumtype_conversion_functions.cc
    stage1_2/stage1_2.cc
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
    stage3/remove_forward_dependencies.cc
    util/library_path.cc)
add_dependencies(matiec_frontend matiec_parser)
target_link_libraries(matiec_frontend PUBLIC matiec_options)
target_compile_definitions(matiec_frontend PRIVATE
    DEFAULT_LIBDIR="${CMAKE_CURRENT_SOURCE_DIR}/lib" YY_BUF_SIZE=65536)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Preserve the legacy parser flags without relaxing the other stages.
    set_source_files_properties(
        "${parser_dir}/iec_bison.cc" "${parser_dir}/iec_flex.cc"
        stage1_2/create_enumtype_conversion_functions.cc stage1_2/stage1_2.cc
        PROPERTIES COMPILE_OPTIONS "-fpermissive;-Wno-free-nonheap-object")
endif()

add_library(matiec_stage4_common OBJECT stage4/stage4.cc)
target_link_libraries(matiec_stage4_common PUBLIC matiec_options)

# generate_c.cc includes the other generate_c_*.cc files; do not compile them separately.
add_executable(iec2c main.cc stage4/generate_c/generate_c.cc)
add_executable(iec2iec main.cc stage4/generate_iec/generate_iec.cc)
foreach(compiler IN ITEMS iec2c iec2iec)
    target_link_libraries(${compiler} PRIVATE matiec_frontend matiec_stage4_common)
    set_target_properties(${compiler} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
endforeach()
if(MSVC)
    target_sources(matiec_frontend PRIVATE util/getopt.cc)
endif()

install(TARGETS iec2c iec2iec RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
install(FILES COPYING DESTINATION "${CMAKE_INSTALL_DATADIR}/matiec")
install(DIRECTORY lib/ DESTINATION "${CMAKE_INSTALL_DATADIR}/matiec/lib"
    FILES_MATCHING PATTERN "*.txt" PATTERN "*.h" PATTERN "*.pycpp"
    PATTERN "COPYING.LESSER")

if(BUILD_TESTING)
    add_subdirectory(cmake/tests)
endif()
