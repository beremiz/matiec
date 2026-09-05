(* A signed array index must compare correctly against an unsigned bound. *)

TYPE
  large_index_array : ARRAY [4294967296..4294967297] OF DINT;
END_TYPE

PROGRAM program0
  VAR
    values : large_index_array;
    result : DINT;
  END_VAR

  result := values[0];
END_PROGRAM

CONFIGURATION config
  RESOURCE resource1 ON PLC
    TASK main_task(INTERVAL := T#1000ms, PRIORITY := 0);
    PROGRAM instance0 WITH main_task : program0;
  END_RESOURCE
END_CONFIGURATION
