file(MAKE_DIRECTORY "${OUTPUT_DIR}")
execute_process(COMMAND "${COMPILER}" -f -l -p -I "${LIBRARY_DIR}"
    -T "${OUTPUT_DIR}" "${INPUT}"
    WORKING_DIRECTORY "${OUTPUT_DIR}"
    RESULT_VARIABLE status OUTPUT_VARIABLE output ERROR_VARIABLE errors)
file(WRITE "${OUTPUT_DIR}/stdout.txt" "${output}")
file(WRITE "${OUTPUT_DIR}/stderr.txt" "${errors}")
if("${output}\n${errors}" MATCHES "Internal compiler error")
    message(FATAL_ERROR "Internal compiler error: ${errors}")
endif()
if(TEST_NAME MATCHES "^bad_")
    if(NOT status STREQUAL "1" OR errors STREQUAL "")
        message(FATAL_ERROR "Expected a diagnostic and rejection, got ${status}: ${errors}")
    endif()
elseif(NOT status STREQUAL "0")
    message(FATAL_ERROR "Expected acceptance, got ${status}: ${errors}")
else()
    file(GLOB generated_sources "${OUTPUT_DIR}/*.c")
    list(FILTER generated_sources EXCLUDE REGEX "/POUS\\.c$")
    if(NOT generated_sources)
        message(FATAL_ERROR "No generated C translation units")
    endif()
    foreach(source IN LISTS generated_sources)
        get_filename_component(name "${source}" NAME)
        if(NOT C_COMPILER)
            continue()
        endif()
        execute_process(COMMAND "${C_COMPILER}" -fsyntax-only -Wall -Wextra -Wno-unused
            "-I${OUTPUT_DIR}" "-I${LIBRARY_DIR}/C" "${name}"
            WORKING_DIRECTORY "${OUTPUT_DIR}"
            RESULT_VARIABLE c_status OUTPUT_VARIABLE c_output ERROR_VARIABLE c_errors)
        if(NOT c_status STREQUAL "0" OR
           "${c_output}\n${c_errors}" MATCHES "(^|\n)(POUS|config|resource[0-9]*)\\.[ch]:")
            message(FATAL_ERROR "Generated C failed validation: ${c_output}${c_errors}")
        endif()
    endforeach()
endif()
