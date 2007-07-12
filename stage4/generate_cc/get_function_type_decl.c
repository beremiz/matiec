
/****
 * IEC 61131-3 standard function lib
 * generated code, do not edit by hand
 */
function_type_t get_function_type(identifier_c *function_name) {

if (!strcasecmp(function_name->value, "BOOL_TO_SINT"))
    return function_bool_to_sint;

if (!strcasecmp(function_name->value, "BOOL_TO_INT"))
    return function_bool_to_int;

if (!strcasecmp(function_name->value, "BOOL_TO_DINT"))
    return function_bool_to_dint;

if (!strcasecmp(function_name->value, "BOOL_TO_LINT"))
    return function_bool_to_lint;

if (!strcasecmp(function_name->value, "BOOL_TO_USINT"))
    return function_bool_to_usint;

if (!strcasecmp(function_name->value, "BOOL_TO_UINT"))
    return function_bool_to_uint;

if (!strcasecmp(function_name->value, "BOOL_TO_UDINT"))
    return function_bool_to_udint;

if (!strcasecmp(function_name->value, "BOOL_TO_ULINT"))
    return function_bool_to_ulint;

if (!strcasecmp(function_name->value, "BOOL_TO_REAL"))
    return function_bool_to_real;

if (!strcasecmp(function_name->value, "BOOL_TO_LREAL"))
    return function_bool_to_lreal;

if (!strcasecmp(function_name->value, "BOOL_TO_TIME"))
    return function_bool_to_time;

if (!strcasecmp(function_name->value, "BOOL_TO_DATE"))
    return function_bool_to_date;

if (!strcasecmp(function_name->value, "BOOL_TO_TOD"))
    return function_bool_to_tod;

if (!strcasecmp(function_name->value, "BOOL_TO_DT"))
    return function_bool_to_dt;

if (!strcasecmp(function_name->value, "BOOL_TO_STRING"))
    return function_bool_to_string;

if (!strcasecmp(function_name->value, "BOOL_TO_BYTE"))
    return function_bool_to_byte;

if (!strcasecmp(function_name->value, "BOOL_TO_WORD"))
    return function_bool_to_word;

if (!strcasecmp(function_name->value, "BOOL_TO_DWORD"))
    return function_bool_to_dword;

if (!strcasecmp(function_name->value, "BOOL_TO_LWORD"))
    return function_bool_to_lword;

if (!strcasecmp(function_name->value, "SINT_TO_BOOL"))
    return function_sint_to_bool;

if (!strcasecmp(function_name->value, "SINT_TO_INT"))
    return function_sint_to_int;

if (!strcasecmp(function_name->value, "SINT_TO_DINT"))
    return function_sint_to_dint;

if (!strcasecmp(function_name->value, "SINT_TO_LINT"))
    return function_sint_to_lint;

if (!strcasecmp(function_name->value, "SINT_TO_USINT"))
    return function_sint_to_usint;

if (!strcasecmp(function_name->value, "SINT_TO_UINT"))
    return function_sint_to_uint;

if (!strcasecmp(function_name->value, "SINT_TO_UDINT"))
    return function_sint_to_udint;

if (!strcasecmp(function_name->value, "SINT_TO_ULINT"))
    return function_sint_to_ulint;

if (!strcasecmp(function_name->value, "SINT_TO_REAL"))
    return function_sint_to_real;

if (!strcasecmp(function_name->value, "SINT_TO_LREAL"))
    return function_sint_to_lreal;

if (!strcasecmp(function_name->value, "SINT_TO_TIME"))
    return function_sint_to_time;

if (!strcasecmp(function_name->value, "SINT_TO_DATE"))
    return function_sint_to_date;

if (!strcasecmp(function_name->value, "SINT_TO_TOD"))
    return function_sint_to_tod;

if (!strcasecmp(function_name->value, "SINT_TO_DT"))
    return function_sint_to_dt;

if (!strcasecmp(function_name->value, "SINT_TO_STRING"))
    return function_sint_to_string;

if (!strcasecmp(function_name->value, "SINT_TO_BYTE"))
    return function_sint_to_byte;

if (!strcasecmp(function_name->value, "SINT_TO_WORD"))
    return function_sint_to_word;

if (!strcasecmp(function_name->value, "SINT_TO_DWORD"))
    return function_sint_to_dword;

if (!strcasecmp(function_name->value, "SINT_TO_LWORD"))
    return function_sint_to_lword;

if (!strcasecmp(function_name->value, "INT_TO_BOOL"))
    return function_int_to_bool;

if (!strcasecmp(function_name->value, "INT_TO_SINT"))
    return function_int_to_sint;

if (!strcasecmp(function_name->value, "INT_TO_DINT"))
    return function_int_to_dint;

if (!strcasecmp(function_name->value, "INT_TO_LINT"))
    return function_int_to_lint;

if (!strcasecmp(function_name->value, "INT_TO_USINT"))
    return function_int_to_usint;

if (!strcasecmp(function_name->value, "INT_TO_UINT"))
    return function_int_to_uint;

if (!strcasecmp(function_name->value, "INT_TO_UDINT"))
    return function_int_to_udint;

if (!strcasecmp(function_name->value, "INT_TO_ULINT"))
    return function_int_to_ulint;

if (!strcasecmp(function_name->value, "INT_TO_REAL"))
    return function_int_to_real;

if (!strcasecmp(function_name->value, "INT_TO_LREAL"))
    return function_int_to_lreal;

if (!strcasecmp(function_name->value, "INT_TO_TIME"))
    return function_int_to_time;

if (!strcasecmp(function_name->value, "INT_TO_DATE"))
    return function_int_to_date;

if (!strcasecmp(function_name->value, "INT_TO_TOD"))
    return function_int_to_tod;

if (!strcasecmp(function_name->value, "INT_TO_DT"))
    return function_int_to_dt;

if (!strcasecmp(function_name->value, "INT_TO_STRING"))
    return function_int_to_string;

if (!strcasecmp(function_name->value, "INT_TO_BYTE"))
    return function_int_to_byte;

if (!strcasecmp(function_name->value, "INT_TO_WORD"))
    return function_int_to_word;

if (!strcasecmp(function_name->value, "INT_TO_DWORD"))
    return function_int_to_dword;

if (!strcasecmp(function_name->value, "INT_TO_LWORD"))
    return function_int_to_lword;

if (!strcasecmp(function_name->value, "DINT_TO_BOOL"))
    return function_dint_to_bool;

if (!strcasecmp(function_name->value, "DINT_TO_SINT"))
    return function_dint_to_sint;

if (!strcasecmp(function_name->value, "DINT_TO_INT"))
    return function_dint_to_int;

if (!strcasecmp(function_name->value, "DINT_TO_LINT"))
    return function_dint_to_lint;

if (!strcasecmp(function_name->value, "DINT_TO_USINT"))
    return function_dint_to_usint;

if (!strcasecmp(function_name->value, "DINT_TO_UINT"))
    return function_dint_to_uint;

if (!strcasecmp(function_name->value, "DINT_TO_UDINT"))
    return function_dint_to_udint;

if (!strcasecmp(function_name->value, "DINT_TO_ULINT"))
    return function_dint_to_ulint;

if (!strcasecmp(function_name->value, "DINT_TO_REAL"))
    return function_dint_to_real;

if (!strcasecmp(function_name->value, "DINT_TO_LREAL"))
    return function_dint_to_lreal;

if (!strcasecmp(function_name->value, "DINT_TO_TIME"))
    return function_dint_to_time;

if (!strcasecmp(function_name->value, "DINT_TO_DATE"))
    return function_dint_to_date;

if (!strcasecmp(function_name->value, "DINT_TO_TOD"))
    return function_dint_to_tod;

if (!strcasecmp(function_name->value, "DINT_TO_DT"))
    return function_dint_to_dt;

if (!strcasecmp(function_name->value, "DINT_TO_STRING"))
    return function_dint_to_string;

if (!strcasecmp(function_name->value, "DINT_TO_BYTE"))
    return function_dint_to_byte;

if (!strcasecmp(function_name->value, "DINT_TO_WORD"))
    return function_dint_to_word;

if (!strcasecmp(function_name->value, "DINT_TO_DWORD"))
    return function_dint_to_dword;

if (!strcasecmp(function_name->value, "DINT_TO_LWORD"))
    return function_dint_to_lword;

if (!strcasecmp(function_name->value, "LINT_TO_BOOL"))
    return function_lint_to_bool;

if (!strcasecmp(function_name->value, "LINT_TO_SINT"))
    return function_lint_to_sint;

if (!strcasecmp(function_name->value, "LINT_TO_INT"))
    return function_lint_to_int;

if (!strcasecmp(function_name->value, "LINT_TO_DINT"))
    return function_lint_to_dint;

if (!strcasecmp(function_name->value, "LINT_TO_USINT"))
    return function_lint_to_usint;

if (!strcasecmp(function_name->value, "LINT_TO_UINT"))
    return function_lint_to_uint;

if (!strcasecmp(function_name->value, "LINT_TO_UDINT"))
    return function_lint_to_udint;

if (!strcasecmp(function_name->value, "LINT_TO_ULINT"))
    return function_lint_to_ulint;

if (!strcasecmp(function_name->value, "LINT_TO_REAL"))
    return function_lint_to_real;

if (!strcasecmp(function_name->value, "LINT_TO_LREAL"))
    return function_lint_to_lreal;

if (!strcasecmp(function_name->value, "LINT_TO_TIME"))
    return function_lint_to_time;

if (!strcasecmp(function_name->value, "LINT_TO_DATE"))
    return function_lint_to_date;

if (!strcasecmp(function_name->value, "LINT_TO_TOD"))
    return function_lint_to_tod;

if (!strcasecmp(function_name->value, "LINT_TO_DT"))
    return function_lint_to_dt;

if (!strcasecmp(function_name->value, "LINT_TO_STRING"))
    return function_lint_to_string;

if (!strcasecmp(function_name->value, "LINT_TO_BYTE"))
    return function_lint_to_byte;

if (!strcasecmp(function_name->value, "LINT_TO_WORD"))
    return function_lint_to_word;

if (!strcasecmp(function_name->value, "LINT_TO_DWORD"))
    return function_lint_to_dword;

if (!strcasecmp(function_name->value, "LINT_TO_LWORD"))
    return function_lint_to_lword;

if (!strcasecmp(function_name->value, "USINT_TO_BOOL"))
    return function_usint_to_bool;

if (!strcasecmp(function_name->value, "USINT_TO_SINT"))
    return function_usint_to_sint;

if (!strcasecmp(function_name->value, "USINT_TO_INT"))
    return function_usint_to_int;

if (!strcasecmp(function_name->value, "USINT_TO_DINT"))
    return function_usint_to_dint;

if (!strcasecmp(function_name->value, "USINT_TO_LINT"))
    return function_usint_to_lint;

if (!strcasecmp(function_name->value, "USINT_TO_UINT"))
    return function_usint_to_uint;

if (!strcasecmp(function_name->value, "USINT_TO_UDINT"))
    return function_usint_to_udint;

if (!strcasecmp(function_name->value, "USINT_TO_ULINT"))
    return function_usint_to_ulint;

if (!strcasecmp(function_name->value, "USINT_TO_REAL"))
    return function_usint_to_real;

if (!strcasecmp(function_name->value, "USINT_TO_LREAL"))
    return function_usint_to_lreal;

if (!strcasecmp(function_name->value, "USINT_TO_TIME"))
    return function_usint_to_time;

if (!strcasecmp(function_name->value, "USINT_TO_DATE"))
    return function_usint_to_date;

if (!strcasecmp(function_name->value, "USINT_TO_TOD"))
    return function_usint_to_tod;

if (!strcasecmp(function_name->value, "USINT_TO_DT"))
    return function_usint_to_dt;

if (!strcasecmp(function_name->value, "USINT_TO_STRING"))
    return function_usint_to_string;

if (!strcasecmp(function_name->value, "USINT_TO_BYTE"))
    return function_usint_to_byte;

if (!strcasecmp(function_name->value, "USINT_TO_WORD"))
    return function_usint_to_word;

if (!strcasecmp(function_name->value, "USINT_TO_DWORD"))
    return function_usint_to_dword;

if (!strcasecmp(function_name->value, "USINT_TO_LWORD"))
    return function_usint_to_lword;

if (!strcasecmp(function_name->value, "UINT_TO_BOOL"))
    return function_uint_to_bool;

if (!strcasecmp(function_name->value, "UINT_TO_SINT"))
    return function_uint_to_sint;

if (!strcasecmp(function_name->value, "UINT_TO_INT"))
    return function_uint_to_int;

if (!strcasecmp(function_name->value, "UINT_TO_DINT"))
    return function_uint_to_dint;

if (!strcasecmp(function_name->value, "UINT_TO_LINT"))
    return function_uint_to_lint;

if (!strcasecmp(function_name->value, "UINT_TO_USINT"))
    return function_uint_to_usint;

if (!strcasecmp(function_name->value, "UINT_TO_UDINT"))
    return function_uint_to_udint;

if (!strcasecmp(function_name->value, "UINT_TO_ULINT"))
    return function_uint_to_ulint;

if (!strcasecmp(function_name->value, "UINT_TO_REAL"))
    return function_uint_to_real;

if (!strcasecmp(function_name->value, "UINT_TO_LREAL"))
    return function_uint_to_lreal;

if (!strcasecmp(function_name->value, "UINT_TO_TIME"))
    return function_uint_to_time;

if (!strcasecmp(function_name->value, "UINT_TO_DATE"))
    return function_uint_to_date;

if (!strcasecmp(function_name->value, "UINT_TO_TOD"))
    return function_uint_to_tod;

if (!strcasecmp(function_name->value, "UINT_TO_DT"))
    return function_uint_to_dt;

if (!strcasecmp(function_name->value, "UINT_TO_STRING"))
    return function_uint_to_string;

if (!strcasecmp(function_name->value, "UINT_TO_BYTE"))
    return function_uint_to_byte;

if (!strcasecmp(function_name->value, "UINT_TO_WORD"))
    return function_uint_to_word;

if (!strcasecmp(function_name->value, "UINT_TO_DWORD"))
    return function_uint_to_dword;

if (!strcasecmp(function_name->value, "UINT_TO_LWORD"))
    return function_uint_to_lword;

if (!strcasecmp(function_name->value, "UDINT_TO_BOOL"))
    return function_udint_to_bool;

if (!strcasecmp(function_name->value, "UDINT_TO_SINT"))
    return function_udint_to_sint;

if (!strcasecmp(function_name->value, "UDINT_TO_INT"))
    return function_udint_to_int;

if (!strcasecmp(function_name->value, "UDINT_TO_DINT"))
    return function_udint_to_dint;

if (!strcasecmp(function_name->value, "UDINT_TO_LINT"))
    return function_udint_to_lint;

if (!strcasecmp(function_name->value, "UDINT_TO_USINT"))
    return function_udint_to_usint;

if (!strcasecmp(function_name->value, "UDINT_TO_UINT"))
    return function_udint_to_uint;

if (!strcasecmp(function_name->value, "UDINT_TO_ULINT"))
    return function_udint_to_ulint;

if (!strcasecmp(function_name->value, "UDINT_TO_REAL"))
    return function_udint_to_real;

if (!strcasecmp(function_name->value, "UDINT_TO_LREAL"))
    return function_udint_to_lreal;

if (!strcasecmp(function_name->value, "UDINT_TO_TIME"))
    return function_udint_to_time;

if (!strcasecmp(function_name->value, "UDINT_TO_DATE"))
    return function_udint_to_date;

if (!strcasecmp(function_name->value, "UDINT_TO_TOD"))
    return function_udint_to_tod;

if (!strcasecmp(function_name->value, "UDINT_TO_DT"))
    return function_udint_to_dt;

if (!strcasecmp(function_name->value, "UDINT_TO_STRING"))
    return function_udint_to_string;

if (!strcasecmp(function_name->value, "UDINT_TO_BYTE"))
    return function_udint_to_byte;

if (!strcasecmp(function_name->value, "UDINT_TO_WORD"))
    return function_udint_to_word;

if (!strcasecmp(function_name->value, "UDINT_TO_DWORD"))
    return function_udint_to_dword;

if (!strcasecmp(function_name->value, "UDINT_TO_LWORD"))
    return function_udint_to_lword;

if (!strcasecmp(function_name->value, "ULINT_TO_BOOL"))
    return function_ulint_to_bool;

if (!strcasecmp(function_name->value, "ULINT_TO_SINT"))
    return function_ulint_to_sint;

if (!strcasecmp(function_name->value, "ULINT_TO_INT"))
    return function_ulint_to_int;

if (!strcasecmp(function_name->value, "ULINT_TO_DINT"))
    return function_ulint_to_dint;

if (!strcasecmp(function_name->value, "ULINT_TO_LINT"))
    return function_ulint_to_lint;

if (!strcasecmp(function_name->value, "ULINT_TO_USINT"))
    return function_ulint_to_usint;

if (!strcasecmp(function_name->value, "ULINT_TO_UINT"))
    return function_ulint_to_uint;

if (!strcasecmp(function_name->value, "ULINT_TO_UDINT"))
    return function_ulint_to_udint;

if (!strcasecmp(function_name->value, "ULINT_TO_REAL"))
    return function_ulint_to_real;

if (!strcasecmp(function_name->value, "ULINT_TO_LREAL"))
    return function_ulint_to_lreal;

if (!strcasecmp(function_name->value, "ULINT_TO_TIME"))
    return function_ulint_to_time;

if (!strcasecmp(function_name->value, "ULINT_TO_DATE"))
    return function_ulint_to_date;

if (!strcasecmp(function_name->value, "ULINT_TO_TOD"))
    return function_ulint_to_tod;

if (!strcasecmp(function_name->value, "ULINT_TO_DT"))
    return function_ulint_to_dt;

if (!strcasecmp(function_name->value, "ULINT_TO_STRING"))
    return function_ulint_to_string;

if (!strcasecmp(function_name->value, "ULINT_TO_BYTE"))
    return function_ulint_to_byte;

if (!strcasecmp(function_name->value, "ULINT_TO_WORD"))
    return function_ulint_to_word;

if (!strcasecmp(function_name->value, "ULINT_TO_DWORD"))
    return function_ulint_to_dword;

if (!strcasecmp(function_name->value, "ULINT_TO_LWORD"))
    return function_ulint_to_lword;

if (!strcasecmp(function_name->value, "REAL_TO_BOOL"))
    return function_real_to_bool;

if (!strcasecmp(function_name->value, "REAL_TO_SINT"))
    return function_real_to_sint;

if (!strcasecmp(function_name->value, "REAL_TO_INT"))
    return function_real_to_int;

if (!strcasecmp(function_name->value, "REAL_TO_DINT"))
    return function_real_to_dint;

if (!strcasecmp(function_name->value, "REAL_TO_LINT"))
    return function_real_to_lint;

if (!strcasecmp(function_name->value, "REAL_TO_USINT"))
    return function_real_to_usint;

if (!strcasecmp(function_name->value, "REAL_TO_UINT"))
    return function_real_to_uint;

if (!strcasecmp(function_name->value, "REAL_TO_UDINT"))
    return function_real_to_udint;

if (!strcasecmp(function_name->value, "REAL_TO_ULINT"))
    return function_real_to_ulint;

if (!strcasecmp(function_name->value, "REAL_TO_LREAL"))
    return function_real_to_lreal;

if (!strcasecmp(function_name->value, "REAL_TO_TIME"))
    return function_real_to_time;

if (!strcasecmp(function_name->value, "REAL_TO_DATE"))
    return function_real_to_date;

if (!strcasecmp(function_name->value, "REAL_TO_TOD"))
    return function_real_to_tod;

if (!strcasecmp(function_name->value, "REAL_TO_DT"))
    return function_real_to_dt;

if (!strcasecmp(function_name->value, "REAL_TO_STRING"))
    return function_real_to_string;

if (!strcasecmp(function_name->value, "REAL_TO_BYTE"))
    return function_real_to_byte;

if (!strcasecmp(function_name->value, "REAL_TO_WORD"))
    return function_real_to_word;

if (!strcasecmp(function_name->value, "REAL_TO_DWORD"))
    return function_real_to_dword;

if (!strcasecmp(function_name->value, "REAL_TO_LWORD"))
    return function_real_to_lword;

if (!strcasecmp(function_name->value, "LREAL_TO_BOOL"))
    return function_lreal_to_bool;

if (!strcasecmp(function_name->value, "LREAL_TO_SINT"))
    return function_lreal_to_sint;

if (!strcasecmp(function_name->value, "LREAL_TO_INT"))
    return function_lreal_to_int;

if (!strcasecmp(function_name->value, "LREAL_TO_DINT"))
    return function_lreal_to_dint;

if (!strcasecmp(function_name->value, "LREAL_TO_LINT"))
    return function_lreal_to_lint;

if (!strcasecmp(function_name->value, "LREAL_TO_USINT"))
    return function_lreal_to_usint;

if (!strcasecmp(function_name->value, "LREAL_TO_UINT"))
    return function_lreal_to_uint;

if (!strcasecmp(function_name->value, "LREAL_TO_UDINT"))
    return function_lreal_to_udint;

if (!strcasecmp(function_name->value, "LREAL_TO_ULINT"))
    return function_lreal_to_ulint;

if (!strcasecmp(function_name->value, "LREAL_TO_REAL"))
    return function_lreal_to_real;

if (!strcasecmp(function_name->value, "LREAL_TO_TIME"))
    return function_lreal_to_time;

if (!strcasecmp(function_name->value, "LREAL_TO_DATE"))
    return function_lreal_to_date;

if (!strcasecmp(function_name->value, "LREAL_TO_TOD"))
    return function_lreal_to_tod;

if (!strcasecmp(function_name->value, "LREAL_TO_DT"))
    return function_lreal_to_dt;

if (!strcasecmp(function_name->value, "LREAL_TO_STRING"))
    return function_lreal_to_string;

if (!strcasecmp(function_name->value, "LREAL_TO_BYTE"))
    return function_lreal_to_byte;

if (!strcasecmp(function_name->value, "LREAL_TO_WORD"))
    return function_lreal_to_word;

if (!strcasecmp(function_name->value, "LREAL_TO_DWORD"))
    return function_lreal_to_dword;

if (!strcasecmp(function_name->value, "LREAL_TO_LWORD"))
    return function_lreal_to_lword;

if (!strcasecmp(function_name->value, "TIME_TO_BOOL"))
    return function_time_to_bool;

if (!strcasecmp(function_name->value, "TIME_TO_SINT"))
    return function_time_to_sint;

if (!strcasecmp(function_name->value, "TIME_TO_INT"))
    return function_time_to_int;

if (!strcasecmp(function_name->value, "TIME_TO_DINT"))
    return function_time_to_dint;

if (!strcasecmp(function_name->value, "TIME_TO_LINT"))
    return function_time_to_lint;

if (!strcasecmp(function_name->value, "TIME_TO_USINT"))
    return function_time_to_usint;

if (!strcasecmp(function_name->value, "TIME_TO_UINT"))
    return function_time_to_uint;

if (!strcasecmp(function_name->value, "TIME_TO_UDINT"))
    return function_time_to_udint;

if (!strcasecmp(function_name->value, "TIME_TO_ULINT"))
    return function_time_to_ulint;

if (!strcasecmp(function_name->value, "TIME_TO_REAL"))
    return function_time_to_real;

if (!strcasecmp(function_name->value, "TIME_TO_LREAL"))
    return function_time_to_lreal;

if (!strcasecmp(function_name->value, "TIME_TO_STRING"))
    return function_time_to_string;

if (!strcasecmp(function_name->value, "TIME_TO_BYTE"))
    return function_time_to_byte;

if (!strcasecmp(function_name->value, "TIME_TO_WORD"))
    return function_time_to_word;

if (!strcasecmp(function_name->value, "TIME_TO_DWORD"))
    return function_time_to_dword;

if (!strcasecmp(function_name->value, "TIME_TO_LWORD"))
    return function_time_to_lword;

if (!strcasecmp(function_name->value, "DATE_TO_BOOL"))
    return function_date_to_bool;

if (!strcasecmp(function_name->value, "DATE_TO_SINT"))
    return function_date_to_sint;

if (!strcasecmp(function_name->value, "DATE_TO_INT"))
    return function_date_to_int;

if (!strcasecmp(function_name->value, "DATE_TO_DINT"))
    return function_date_to_dint;

if (!strcasecmp(function_name->value, "DATE_TO_LINT"))
    return function_date_to_lint;

if (!strcasecmp(function_name->value, "DATE_TO_USINT"))
    return function_date_to_usint;

if (!strcasecmp(function_name->value, "DATE_TO_UINT"))
    return function_date_to_uint;

if (!strcasecmp(function_name->value, "DATE_TO_UDINT"))
    return function_date_to_udint;

if (!strcasecmp(function_name->value, "DATE_TO_ULINT"))
    return function_date_to_ulint;

if (!strcasecmp(function_name->value, "DATE_TO_REAL"))
    return function_date_to_real;

if (!strcasecmp(function_name->value, "DATE_TO_LREAL"))
    return function_date_to_lreal;

if (!strcasecmp(function_name->value, "DATE_TO_STRING"))
    return function_date_to_string;

if (!strcasecmp(function_name->value, "DATE_TO_BYTE"))
    return function_date_to_byte;

if (!strcasecmp(function_name->value, "DATE_TO_WORD"))
    return function_date_to_word;

if (!strcasecmp(function_name->value, "DATE_TO_DWORD"))
    return function_date_to_dword;

if (!strcasecmp(function_name->value, "DATE_TO_LWORD"))
    return function_date_to_lword;

if (!strcasecmp(function_name->value, "TOD_TO_BOOL"))
    return function_tod_to_bool;

if (!strcasecmp(function_name->value, "TOD_TO_SINT"))
    return function_tod_to_sint;

if (!strcasecmp(function_name->value, "TOD_TO_INT"))
    return function_tod_to_int;

if (!strcasecmp(function_name->value, "TOD_TO_DINT"))
    return function_tod_to_dint;

if (!strcasecmp(function_name->value, "TOD_TO_LINT"))
    return function_tod_to_lint;

if (!strcasecmp(function_name->value, "TOD_TO_USINT"))
    return function_tod_to_usint;

if (!strcasecmp(function_name->value, "TOD_TO_UINT"))
    return function_tod_to_uint;

if (!strcasecmp(function_name->value, "TOD_TO_UDINT"))
    return function_tod_to_udint;

if (!strcasecmp(function_name->value, "TOD_TO_ULINT"))
    return function_tod_to_ulint;

if (!strcasecmp(function_name->value, "TOD_TO_REAL"))
    return function_tod_to_real;

if (!strcasecmp(function_name->value, "TOD_TO_LREAL"))
    return function_tod_to_lreal;

if (!strcasecmp(function_name->value, "TOD_TO_STRING"))
    return function_tod_to_string;

if (!strcasecmp(function_name->value, "TOD_TO_BYTE"))
    return function_tod_to_byte;

if (!strcasecmp(function_name->value, "TOD_TO_WORD"))
    return function_tod_to_word;

if (!strcasecmp(function_name->value, "TOD_TO_DWORD"))
    return function_tod_to_dword;

if (!strcasecmp(function_name->value, "TOD_TO_LWORD"))
    return function_tod_to_lword;

if (!strcasecmp(function_name->value, "DT_TO_BOOL"))
    return function_dt_to_bool;

if (!strcasecmp(function_name->value, "DT_TO_SINT"))
    return function_dt_to_sint;

if (!strcasecmp(function_name->value, "DT_TO_INT"))
    return function_dt_to_int;

if (!strcasecmp(function_name->value, "DT_TO_DINT"))
    return function_dt_to_dint;

if (!strcasecmp(function_name->value, "DT_TO_LINT"))
    return function_dt_to_lint;

if (!strcasecmp(function_name->value, "DT_TO_USINT"))
    return function_dt_to_usint;

if (!strcasecmp(function_name->value, "DT_TO_UINT"))
    return function_dt_to_uint;

if (!strcasecmp(function_name->value, "DT_TO_UDINT"))
    return function_dt_to_udint;

if (!strcasecmp(function_name->value, "DT_TO_ULINT"))
    return function_dt_to_ulint;

if (!strcasecmp(function_name->value, "DT_TO_REAL"))
    return function_dt_to_real;

if (!strcasecmp(function_name->value, "DT_TO_LREAL"))
    return function_dt_to_lreal;

if (!strcasecmp(function_name->value, "DT_TO_STRING"))
    return function_dt_to_string;

if (!strcasecmp(function_name->value, "DT_TO_BYTE"))
    return function_dt_to_byte;

if (!strcasecmp(function_name->value, "DT_TO_WORD"))
    return function_dt_to_word;

if (!strcasecmp(function_name->value, "DT_TO_DWORD"))
    return function_dt_to_dword;

if (!strcasecmp(function_name->value, "DT_TO_LWORD"))
    return function_dt_to_lword;

if (!strcasecmp(function_name->value, "STRING_TO_BOOL"))
    return function_string_to_bool;

if (!strcasecmp(function_name->value, "STRING_TO_SINT"))
    return function_string_to_sint;

if (!strcasecmp(function_name->value, "STRING_TO_INT"))
    return function_string_to_int;

if (!strcasecmp(function_name->value, "STRING_TO_DINT"))
    return function_string_to_dint;

if (!strcasecmp(function_name->value, "STRING_TO_LINT"))
    return function_string_to_lint;

if (!strcasecmp(function_name->value, "STRING_TO_USINT"))
    return function_string_to_usint;

if (!strcasecmp(function_name->value, "STRING_TO_UINT"))
    return function_string_to_uint;

if (!strcasecmp(function_name->value, "STRING_TO_UDINT"))
    return function_string_to_udint;

if (!strcasecmp(function_name->value, "STRING_TO_ULINT"))
    return function_string_to_ulint;

if (!strcasecmp(function_name->value, "STRING_TO_REAL"))
    return function_string_to_real;

if (!strcasecmp(function_name->value, "STRING_TO_LREAL"))
    return function_string_to_lreal;

if (!strcasecmp(function_name->value, "STRING_TO_TIME"))
    return function_string_to_time;

if (!strcasecmp(function_name->value, "STRING_TO_DATE"))
    return function_string_to_date;

if (!strcasecmp(function_name->value, "STRING_TO_TOD"))
    return function_string_to_tod;

if (!strcasecmp(function_name->value, "STRING_TO_DT"))
    return function_string_to_dt;

if (!strcasecmp(function_name->value, "STRING_TO_BYTE"))
    return function_string_to_byte;

if (!strcasecmp(function_name->value, "STRING_TO_WORD"))
    return function_string_to_word;

if (!strcasecmp(function_name->value, "STRING_TO_DWORD"))
    return function_string_to_dword;

if (!strcasecmp(function_name->value, "STRING_TO_LWORD"))
    return function_string_to_lword;

if (!strcasecmp(function_name->value, "BYTE_TO_BOOL"))
    return function_byte_to_bool;

if (!strcasecmp(function_name->value, "BYTE_TO_SINT"))
    return function_byte_to_sint;

if (!strcasecmp(function_name->value, "BYTE_TO_INT"))
    return function_byte_to_int;

if (!strcasecmp(function_name->value, "BYTE_TO_DINT"))
    return function_byte_to_dint;

if (!strcasecmp(function_name->value, "BYTE_TO_LINT"))
    return function_byte_to_lint;

if (!strcasecmp(function_name->value, "BYTE_TO_USINT"))
    return function_byte_to_usint;

if (!strcasecmp(function_name->value, "BYTE_TO_UINT"))
    return function_byte_to_uint;

if (!strcasecmp(function_name->value, "BYTE_TO_UDINT"))
    return function_byte_to_udint;

if (!strcasecmp(function_name->value, "BYTE_TO_ULINT"))
    return function_byte_to_ulint;

if (!strcasecmp(function_name->value, "BYTE_TO_REAL"))
    return function_byte_to_real;

if (!strcasecmp(function_name->value, "BYTE_TO_LREAL"))
    return function_byte_to_lreal;

if (!strcasecmp(function_name->value, "BYTE_TO_TIME"))
    return function_byte_to_time;

if (!strcasecmp(function_name->value, "BYTE_TO_DATE"))
    return function_byte_to_date;

if (!strcasecmp(function_name->value, "BYTE_TO_TOD"))
    return function_byte_to_tod;

if (!strcasecmp(function_name->value, "BYTE_TO_DT"))
    return function_byte_to_dt;

if (!strcasecmp(function_name->value, "BYTE_TO_STRING"))
    return function_byte_to_string;

if (!strcasecmp(function_name->value, "BYTE_TO_WORD"))
    return function_byte_to_word;

if (!strcasecmp(function_name->value, "BYTE_TO_DWORD"))
    return function_byte_to_dword;

if (!strcasecmp(function_name->value, "BYTE_TO_LWORD"))
    return function_byte_to_lword;

if (!strcasecmp(function_name->value, "WORD_TO_BOOL"))
    return function_word_to_bool;

if (!strcasecmp(function_name->value, "WORD_TO_SINT"))
    return function_word_to_sint;

if (!strcasecmp(function_name->value, "WORD_TO_INT"))
    return function_word_to_int;

if (!strcasecmp(function_name->value, "WORD_TO_DINT"))
    return function_word_to_dint;

if (!strcasecmp(function_name->value, "WORD_TO_LINT"))
    return function_word_to_lint;

if (!strcasecmp(function_name->value, "WORD_TO_USINT"))
    return function_word_to_usint;

if (!strcasecmp(function_name->value, "WORD_TO_UINT"))
    return function_word_to_uint;

if (!strcasecmp(function_name->value, "WORD_TO_UDINT"))
    return function_word_to_udint;

if (!strcasecmp(function_name->value, "WORD_TO_ULINT"))
    return function_word_to_ulint;

if (!strcasecmp(function_name->value, "WORD_TO_REAL"))
    return function_word_to_real;

if (!strcasecmp(function_name->value, "WORD_TO_LREAL"))
    return function_word_to_lreal;

if (!strcasecmp(function_name->value, "WORD_TO_TIME"))
    return function_word_to_time;

if (!strcasecmp(function_name->value, "WORD_TO_DATE"))
    return function_word_to_date;

if (!strcasecmp(function_name->value, "WORD_TO_TOD"))
    return function_word_to_tod;

if (!strcasecmp(function_name->value, "WORD_TO_DT"))
    return function_word_to_dt;

if (!strcasecmp(function_name->value, "WORD_TO_STRING"))
    return function_word_to_string;

if (!strcasecmp(function_name->value, "WORD_TO_BYTE"))
    return function_word_to_byte;

if (!strcasecmp(function_name->value, "WORD_TO_DWORD"))
    return function_word_to_dword;

if (!strcasecmp(function_name->value, "WORD_TO_LWORD"))
    return function_word_to_lword;

if (!strcasecmp(function_name->value, "DWORD_TO_BOOL"))
    return function_dword_to_bool;

if (!strcasecmp(function_name->value, "DWORD_TO_SINT"))
    return function_dword_to_sint;

if (!strcasecmp(function_name->value, "DWORD_TO_INT"))
    return function_dword_to_int;

if (!strcasecmp(function_name->value, "DWORD_TO_DINT"))
    return function_dword_to_dint;

if (!strcasecmp(function_name->value, "DWORD_TO_LINT"))
    return function_dword_to_lint;

if (!strcasecmp(function_name->value, "DWORD_TO_USINT"))
    return function_dword_to_usint;

if (!strcasecmp(function_name->value, "DWORD_TO_UINT"))
    return function_dword_to_uint;

if (!strcasecmp(function_name->value, "DWORD_TO_UDINT"))
    return function_dword_to_udint;

if (!strcasecmp(function_name->value, "DWORD_TO_ULINT"))
    return function_dword_to_ulint;

if (!strcasecmp(function_name->value, "DWORD_TO_REAL"))
    return function_dword_to_real;

if (!strcasecmp(function_name->value, "DWORD_TO_LREAL"))
    return function_dword_to_lreal;

if (!strcasecmp(function_name->value, "DWORD_TO_TIME"))
    return function_dword_to_time;

if (!strcasecmp(function_name->value, "DWORD_TO_DATE"))
    return function_dword_to_date;

if (!strcasecmp(function_name->value, "DWORD_TO_TOD"))
    return function_dword_to_tod;

if (!strcasecmp(function_name->value, "DWORD_TO_DT"))
    return function_dword_to_dt;

if (!strcasecmp(function_name->value, "DWORD_TO_STRING"))
    return function_dword_to_string;

if (!strcasecmp(function_name->value, "DWORD_TO_BYTE"))
    return function_dword_to_byte;

if (!strcasecmp(function_name->value, "DWORD_TO_WORD"))
    return function_dword_to_word;

if (!strcasecmp(function_name->value, "DWORD_TO_LWORD"))
    return function_dword_to_lword;

if (!strcasecmp(function_name->value, "LWORD_TO_BOOL"))
    return function_lword_to_bool;

if (!strcasecmp(function_name->value, "LWORD_TO_SINT"))
    return function_lword_to_sint;

if (!strcasecmp(function_name->value, "LWORD_TO_INT"))
    return function_lword_to_int;

if (!strcasecmp(function_name->value, "LWORD_TO_DINT"))
    return function_lword_to_dint;

if (!strcasecmp(function_name->value, "LWORD_TO_LINT"))
    return function_lword_to_lint;

if (!strcasecmp(function_name->value, "LWORD_TO_USINT"))
    return function_lword_to_usint;

if (!strcasecmp(function_name->value, "LWORD_TO_UINT"))
    return function_lword_to_uint;

if (!strcasecmp(function_name->value, "LWORD_TO_UDINT"))
    return function_lword_to_udint;

if (!strcasecmp(function_name->value, "LWORD_TO_ULINT"))
    return function_lword_to_ulint;

if (!strcasecmp(function_name->value, "LWORD_TO_REAL"))
    return function_lword_to_real;

if (!strcasecmp(function_name->value, "LWORD_TO_LREAL"))
    return function_lword_to_lreal;

if (!strcasecmp(function_name->value, "LWORD_TO_TIME"))
    return function_lword_to_time;

if (!strcasecmp(function_name->value, "LWORD_TO_DATE"))
    return function_lword_to_date;

if (!strcasecmp(function_name->value, "LWORD_TO_TOD"))
    return function_lword_to_tod;

if (!strcasecmp(function_name->value, "LWORD_TO_DT"))
    return function_lword_to_dt;

if (!strcasecmp(function_name->value, "LWORD_TO_STRING"))
    return function_lword_to_string;

if (!strcasecmp(function_name->value, "LWORD_TO_BYTE"))
    return function_lword_to_byte;

if (!strcasecmp(function_name->value, "LWORD_TO_WORD"))
    return function_lword_to_word;

if (!strcasecmp(function_name->value, "LWORD_TO_DWORD"))
    return function_lword_to_dword;

if (!strcasecmp(function_name->value, "TRUNC"))
    return function_trunc;

if (!strcasecmp(function_name->value, "BCD_TO_USINT"))
    return function_bcd_to_usint;

if (!strcasecmp(function_name->value, "BCD_TO_UINT"))
    return function_bcd_to_uint;

if (!strcasecmp(function_name->value, "BCD_TO_UDINT"))
    return function_bcd_to_udint;

if (!strcasecmp(function_name->value, "BCD_TO_ULINT"))
    return function_bcd_to_ulint;

if (!strcasecmp(function_name->value, "USINT_TO_BCD"))
    return function_usint_to_bcd;

if (!strcasecmp(function_name->value, "UINT_TO_BCD"))
    return function_uint_to_bcd;

if (!strcasecmp(function_name->value, "UDINT_TO_BCD"))
    return function_udint_to_bcd;

if (!strcasecmp(function_name->value, "ULINT_TO_BCD"))
    return function_ulint_to_bcd;

if (!strcasecmp(function_name->value, "DATE_AND_TIME_TO_TIME_OF_DAY"))
    return function_date_and_time_to_time_of_day;

if (!strcasecmp(function_name->value, "DATE_AND_TIME_TO_DATE"))
    return function_date_and_time_to_date;

if (!strcasecmp(function_name->value, "ABS"))
    return function_abs;

if (!strcasecmp(function_name->value, "SQRT"))
    return function_sqrt;

if (!strcasecmp(function_name->value, "LN"))
    return function_ln;

if (!strcasecmp(function_name->value, "LOG"))
    return function_log;

if (!strcasecmp(function_name->value, "EXP"))
    return function_exp;

if (!strcasecmp(function_name->value, "SIN"))
    return function_sin;

if (!strcasecmp(function_name->value, "COS"))
    return function_cos;

if (!strcasecmp(function_name->value, "TAN"))
    return function_tan;

if (!strcasecmp(function_name->value, "ASIN"))
    return function_asin;

if (!strcasecmp(function_name->value, "ACOS"))
    return function_acos;

if (!strcasecmp(function_name->value, "ATAN"))
    return function_atan;

if (!strcasecmp(function_name->value, "ADD"))
    return function_add;

if (!strcasecmp(function_name->value, "MUL"))
    return function_mul;

if (!strcasecmp(function_name->value, "SUB"))
    return function_sub;

if (!strcasecmp(function_name->value, "DIV"))
    return function_div;

if (!strcasecmp(function_name->value, "MOD"))
    return function_mod;

if (!strcasecmp(function_name->value, "EXPT"))
    return function_expt;

if (!strcasecmp(function_name->value, "MOVE"))
    return function_move;

if (!strcasecmp(function_name->value, "SHL"))
    return function_shl;

if (!strcasecmp(function_name->value, "SHR"))
    return function_shr;

if (!strcasecmp(function_name->value, "ROR"))
    return function_ror;

if (!strcasecmp(function_name->value, "ROL"))
    return function_rol;

if (!strcasecmp(function_name->value, "AND"))
    return function_and;

if (!strcasecmp(function_name->value, "OR"))
    return function_or;

if (!strcasecmp(function_name->value, "XOR"))
    return function_xor;

if (!strcasecmp(function_name->value, "NOT"))
    return function_not;

if (!strcasecmp(function_name->value, "SEL"))
    return function_sel;

if (!strcasecmp(function_name->value, "MAX"))
    return function_max;

if (!strcasecmp(function_name->value, "MIN"))
    return function_min;

if (!strcasecmp(function_name->value, "LIMIT"))
    return function_limit;

if (!strcasecmp(function_name->value, "MUX"))
    return function_mux;

if (!strcasecmp(function_name->value, "GT"))
    return function_gt;

if (!strcasecmp(function_name->value, "GE"))
    return function_ge;

if (!strcasecmp(function_name->value, "EQ"))
    return function_eq;

if (!strcasecmp(function_name->value, "LT"))
    return function_lt;

if (!strcasecmp(function_name->value, "LE"))
    return function_le;

if (!strcasecmp(function_name->value, "NE"))
    return function_ne;

if (!strcasecmp(function_name->value, "LEN"))
    return function_len;

if (!strcasecmp(function_name->value, "LEFT"))
    return function_left;

if (!strcasecmp(function_name->value, "RIGHT"))
    return function_right;

if (!strcasecmp(function_name->value, "MID"))
    return function_mid;

if (!strcasecmp(function_name->value, "CONCAT"))
    return function_concat;

if (!strcasecmp(function_name->value, "INSERT"))
    return function_insert;

if (!strcasecmp(function_name->value, "DELETE"))
    return function_delete;

if (!strcasecmp(function_name->value, "REPLACE"))
    return function_replace;

if (!strcasecmp(function_name->value, "FIND"))
    return function_find;

    else return function_none;
}

