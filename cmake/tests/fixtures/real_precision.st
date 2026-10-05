(* LREAL parsing must not narrow a literal through a 32-bit float. *)
PROGRAM program0
  VAR
    large_value : LREAL := 1.0E100;
  END_VAR
  large_value := large_value + LREAL#1.0;
END_PROGRAM

CONFIGURATION config
  RESOURCE resource1 ON PLC
    TASK main_task(INTERVAL := T#1000ms, PRIORITY := 0);
    PROGRAM instance0 WITH main_task : program0;
  END_RESOURCE
END_CONFIGURATION
