(* Computing a subrange starting at INT64_MIN must not negate INT64_MIN. *)

TYPE
  minimum_bound_array : ARRAY [-9223372036854775808..-9223372036854775807] OF DINT;
END_TYPE

PROGRAM program0
  VAR
    values : minimum_bound_array := [1, 2];
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
