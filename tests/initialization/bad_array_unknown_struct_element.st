(* Test of initial values for structured/array data types. *)

TYPE
  inner : STRUCT
    a : DINT;
    b : DINT;
    c : STRING;
  END_STRUCT;
  arr_inner : ARRAY [1..2] OF inner;
END_TYPE

PROGRAM program0
  VAR
    count : DINT;
    v : arr_inner := [(a := 1, zz := 2, c := 'a'), (a := 3, b := 4, c := 'b')];
  END_VAR

  count := count + 1;
END_PROGRAM

CONFIGURATION config
  RESOURCE resource1 ON PLC
    TASK main_task(INTERVAL := T#1000ms, PRIORITY := 0);
    PROGRAM instance0 WITH main_task : program0;
  END_RESOURCE
END_CONFIGURATION
