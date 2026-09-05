(* The product of individually valid dimensions must not overflow. *)

TYPE
  overflowing_array : ARRAY [0..4294967295, 0..4294967295] OF BOOL;
END_TYPE

PROGRAM program0
  VAR
    values : overflowing_array := [FALSE];
    count : DINT;
  END_VAR

  count := count + 1;
END_PROGRAM

CONFIGURATION config
  RESOURCE resource1 ON PLC
    TASK main_task(INTERVAL := T#1000ms, PRIORITY := 0);
    PROGRAM instance0 WITH main_task : program0;
  END_RESOURCE
END_CONFIGURATION
