(* Test of initial values for structured/array data types. *)

(* KNOWN FAILURE: an array initialization nested inside another array initialization
 * aborts the C code generator (generate_c_vardecl.cc), as it counts the initial values
 * of every nesting level with the same set of counters.
 *)

TYPE
  arr_dint : ARRAY [1..2] OF DINT;
  arr_arr_dint : ARRAY [1..2] OF arr_dint;
END_TYPE

PROGRAM program0
  VAR
    count : DINT;
    v : arr_arr_dint := [[1, 2], [3, 4]];
  END_VAR

  count := count + 1;
END_PROGRAM

CONFIGURATION config
  RESOURCE resource1 ON PLC
    TASK main_task(INTERVAL := T#1000ms, PRIORITY := 0);
    PROGRAM instance0 WITH main_task : program0;
  END_RESOURCE
END_CONFIGURATION
