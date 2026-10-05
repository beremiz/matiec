file(MAKE_DIRECTORY "${OUTPUT_DIR}")
execute_process(COMMAND "${COMPILER}" -I "${LIBRARY_DIR}" "${INPUT}"
    WORKING_DIRECTORY "${OUTPUT_DIR}"
    RESULT_VARIABLE status OUTPUT_VARIABLE output ERROR_VARIABLE errors)
if(NOT status STREQUAL "0")
    message(FATAL_ERROR "IEC generation failed: ${errors}")
endif()
# iec2iec emits the standard library too. Reparse only the user program, since
# the compiler loads the standard library automatically on every invocation.
set(marker "{enable code generation}")
string(FIND "${output}" "${marker}" start REVERSE)
if(start LESS 0)
    message(FATAL_ERROR "Missing user code in generated IEC")
endif()
string(LENGTH "${marker}" marker_length)
math(EXPR start "${start} + ${marker_length}")
string(SUBSTRING "${output}" ${start} -1 user_code)
file(WRITE "${OUTPUT_DIR}/roundtrip.st" "${user_code}")
execute_process(COMMAND "${COMPILER}" -I "${LIBRARY_DIR}" "${OUTPUT_DIR}/roundtrip.st"
    WORKING_DIRECTORY "${OUTPUT_DIR}"
    RESULT_VARIABLE status OUTPUT_VARIABLE output ERROR_VARIABLE errors)
if(NOT status STREQUAL "0")
    message(FATAL_ERROR "Generated IEC could not be parsed: ${errors}")
endif()
