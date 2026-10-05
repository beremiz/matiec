file(MAKE_DIRECTORY "${OUTPUT_DIR}")
configure_file("${INPUT}" "${OUTPUT_DIR}/-input.st" COPYONLY)
execute_process(COMMAND "${COMPILER}" -flp "-I${LIBRARY_DIR}" "-T${OUTPUT_DIR}"
    -- -input.st WORKING_DIRECTORY "${OUTPUT_DIR}"
    RESULT_VARIABLE status OUTPUT_VARIABLE output ERROR_VARIABLE errors)
if(NOT status STREQUAL "0")
    message(FATAL_ERROR "Clustered/attached options or -- failed: ${status}: ${errors}")
endif()
foreach(argument IN ITEMS -I -T -O -z)
    execute_process(COMMAND "${COMPILER}" "${argument}"
        WORKING_DIRECTORY "${OUTPUT_DIR}"
        RESULT_VARIABLE status OUTPUT_VARIABLE output ERROR_VARIABLE errors)
    if(NOT status STREQUAL "1" OR errors STREQUAL "")
        message(FATAL_ERROR "Expected a diagnostic and rejection for ${argument}, got ${status}: ${errors}")
    endif()
endforeach()
