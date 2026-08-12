(* Test of initial values for structured/array data types. *)

TYPE
  colour : (RED, GREEN, BLUE);
  arr_colour : ARRAY [1..2] OF colour := [RED, BLUE];
END_TYPE

PROGRAM program0
  VAR
    count : DINT;
    v : arr_colour;
  END_VAR

  count := count + 1;
END_PROGRAM

CONFIGURATION config
  RESOURCE resource1 ON PLC
    TASK main_task(INTERVAL := T#1000ms, PRIORITY := 0);
    PROGRAM instance0 WITH main_task : program0;
  END_RESOURCE
END_CONFIGURATION
