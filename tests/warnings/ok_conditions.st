(* Conditions of IF, ELSIF, WHILE and CASE that compare a variable with '='.
   They become C if and while statements, that put their condition in
   parentheses, and clang warns about "if ((a == b))" (-Wparentheses-equality). *)

PROGRAM program0
  VAR
    ia : INT;
  END_VAR

  IF ia = 5 THEN
    ia := 0;
  ELSIF ia = 6 THEN
    ia := 1;
  END_IF;
  WHILE ia = 7 DO
    ia := 8;
  END_WHILE;
  CASE ia OF
    1: ia := 2;
    3, 4..5: ia := 6;
  END_CASE;
END_PROGRAM

CONFIGURATION config
  RESOURCE resource1 ON PLC
    TASK main_task(INTERVAL := T#1000ms, PRIORITY := 0);
    PROGRAM instance0 WITH main_task : program0;
  END_RESOURCE
END_CONFIGURATION
