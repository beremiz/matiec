(* Calls of extensible standard functions. Their extensible operands are passed
   through a C "...", so they undergo default argument promotions: REAL ones
   become double, triggering -Wdouble-promotion, and va_start() must not take
   such an operand as its last named parameter (clang's -Wvarargs).
   Calls come from ST, from IL, and from the inline functions that get ENO. *)

FUNCTION_BLOCK fb_il
  VAR_INPUT
    ra, rb : REAL;
  END_VAR
  VAR_OUTPUT
    rmax, rmax2 : REAL;
    smax : SINT;
    ra_gt_rb : BOOL;
  END_VAR
  VAR
    sa : SINT;
  END_VAR
  LD ra
  MAX rb, 1.5
  ST rmax
  MAX(
    IN1 := ra,
    IN2 := rb
  )
  ST rmax2
  LD sa
  MAX 3
  ST smax
  LD ra
  GT rb
  ST ra_gt_rb
END_FUNCTION_BLOCK

PROGRAM program0
  VAR
    sa, sb : SINT;
    ra, rb, rc : REAL;
    ba, bb : BOOL;
    ta, tb : TIME;
    stra, strb : STRING;
    k : INT;
    ok : BOOL;
    il : fb_il;
  END_VAR

  rc := ADD(ra, rb, 2.5);
  rc := MAX(ra, rb);
  rc := MUX(k, ra, rb, rc);
  sa := MUL(sa, sb, 3);
  ba := XOR(ba, bb, TRUE);
  ba := GT(ra, rb, rc);
  ba := EQ(ta, tb);
  stra := CONCAT(stra, strb, 'x');
  rc := ADD(EN := ba, IN1 := ra, IN2 := rb, ENO => ok);
  sa := MAX(EN := ba, IN1 := sa, IN2 := sb, ENO => ok);
  il(ra := ra, rb := rb);
END_PROGRAM

CONFIGURATION config
  RESOURCE resource1 ON PLC
    TASK main_task(INTERVAL := T#1000ms, PRIORITY := 0);
    PROGRAM instance0 WITH main_task : program0;
  END_RESOURCE
END_CONFIGURATION
