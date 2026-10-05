if(IS_ABSOLUTE "${BIN_DIR}" OR IS_ABSOLUTE "${DATA_DIR}")
    message(FATAL_ERROR "The relocation test requires relative install directories")
endif()
set(stage "${OUTPUT_DIR}/original prefix")
set(relocated "${OUTPUT_DIR}/relocated prefix")
execute_process(COMMAND "${CMAKE_COMMAND}" --install "${BUILD_DIR}"
    --config "${CONFIG}" --prefix "${stage}"
    RESULT_VARIABLE status OUTPUT_VARIABLE output ERROR_VARIABLE errors)
if(NOT status STREQUAL "0")
    message(FATAL_ERROR "Installation failed: ${output}${errors}")
endif()
file(COPY "${stage}/" DESTINATION "${relocated}")
# A function present only in this installation proves that the compiler selects
# the relocated library, rather than silently falling back to the source tree.
file(APPEND "${relocated}/${DATA_DIR}/matiec/lib/standard_functions.txt" "
FUNCTION MATIEC_INSTALL_PROBE : DINT
VAR_INPUT
  VALUE : DINT;
END_VAR
MATIEC_INSTALL_PROBE := VALUE;
END_FUNCTION
")
file(READ "${INPUT}" program)
string(REPLACE "count := count + 1;"
    "count := count + MATIEC_INSTALL_PROBE(1);" program "${program}")
file(WRITE "${OUTPUT_DIR}/probe.st" "${program}")
file(MAKE_DIRECTORY "${OUTPUT_DIR}/unrelated directory")
foreach(compiler IN ITEMS iec2c iec2iec)
    execute_process(COMMAND "${relocated}/${BIN_DIR}/${compiler}${EXE_SUFFIX}"
        -T "${OUTPUT_DIR}/unrelated directory" "${OUTPUT_DIR}/probe.st"
        WORKING_DIRECTORY "${OUTPUT_DIR}/unrelated directory"
        RESULT_VARIABLE status OUTPUT_VARIABLE output ERROR_VARIABLE errors)
    if(NOT status STREQUAL "0")
        message(FATAL_ERROR "Relocated ${compiler} failed: ${status}: ${output}${errors}")
    endif()
endforeach()
