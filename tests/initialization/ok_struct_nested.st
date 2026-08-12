(* Test of initial values for structured/array data types. *)

TYPE
  inner : STRUCT
    a : DINT;
    b : DINT;
    c : STRING;
  END_STRUCT;
  rec : STRUCT
    aa : DINT;
    bb : inner;
  END_STRUCT;
END_TYPE

PROGRAM program0
  VAR
    count : DINT;
    v : rec := (aa := 1, bb := (a := 2, b := 3, c := 'a'));
  END_VAR

  count := count + 1;
END_PROGRAM

CONFIGURATION config
  RESOURCE resource1 ON PLC
    TASK main_task(INTERVAL := T#1000ms, PRIORITY := 0);
    PROGRAM instance0 WITH main_task : program0;
  END_RESOURCE
END_CONFIGURATION
