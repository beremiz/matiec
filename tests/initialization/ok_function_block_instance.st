(* Function block instances remain valid in a non-CONSTANT variable block. *)

FUNCTION_BLOCK counter_fb
  VAR
    count : DINT;
  END_VAR

  count := count + 1;
END_FUNCTION_BLOCK

PROGRAM program0
  VAR
    counter : counter_fb;
  END_VAR

  counter();
END_PROGRAM

CONFIGURATION config
  RESOURCE resource1 ON PLC
    TASK main_task(INTERVAL := T#1000ms, PRIORITY := 0);
    PROGRAM instance0 WITH main_task : program0;
  END_RESOURCE
END_CONFIGURATION
