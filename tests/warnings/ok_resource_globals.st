(* Globals of resources, that POUs use as VAR_EXTERNAL, as in Beremiz's
   first_steps example. Their getters (__GET_GLOBAL_<name>) are defined in the
   C file of each resource only, while config.c also includes POUS.c, for the
   constructors of POUs. So do calls to functions with VAR_OUTPUT, that are
   made through inline wrappers. *)

FUNCTION double_it : DINT
  VAR_INPUT
    i : DINT;
  END_VAR
  VAR_OUTPUT
    o : DINT;
  END_VAR
  o := i * 2;
  double_it := o;
END_FUNCTION

FUNCTION_BLOCK fb0
  VAR_EXTERNAL
    resource_global : DINT;
  END_VAR
  VAR
    doubled : DINT;
  END_VAR
  resource_global := double_it(i := resource_global, o => doubled);
END_FUNCTION_BLOCK

PROGRAM program0
  VAR_EXTERNAL
    resource_global : DINT;
    resource_timer : TON;
  END_VAR
  VAR
    fb_instance : fb0;
    doubled : DINT;
  END_VAR
  resource_timer(IN := TRUE, PT := T#1s);
  fb_instance();
  resource_global := double_it(i := resource_global, o => doubled);
END_PROGRAM

CONFIGURATION config
  RESOURCE resource1 ON PLC
    VAR_GLOBAL
      resource_global : DINT := 1;
      resource_timer : TON;
    END_VAR
    TASK main_task(INTERVAL := T#1000ms, PRIORITY := 0);
    PROGRAM instance0 WITH main_task : program0;
  END_RESOURCE
  RESOURCE resource2 ON PLC
    VAR_GLOBAL
      resource_global : DINT := 2;
      resource_timer : TON;
    END_VAR
    TASK main_task(INTERVAL := T#20ms, PRIORITY := 0);
    PROGRAM instance1 WITH main_task : program0;
  END_RESOURCE
END_CONFIGURATION
