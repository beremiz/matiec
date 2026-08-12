(* Test of initial values for structured/array data types. *)

TYPE
  colour : (RED, GREEN, BLUE);
  rec : STRUCT
    kkk : DINT;
    col : colour;
  END_STRUCT;
END_TYPE

PROGRAM program0
  VAR
    count : DINT;
    v : rec := (kkk := 1, col := BLUE);
  END_VAR

  count := count + 1;
END_PROGRAM

CONFIGURATION config
  RESOURCE resource1 ON PLC
    TASK main_task(INTERVAL := T#1000ms, PRIORITY := 0);
    PROGRAM instance0 WITH main_task : program0;
  END_RESOURCE
END_CONFIGURATION
