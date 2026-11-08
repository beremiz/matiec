#ifndef _IEC_STD_FB_IMPL
#define _IEC_STD_FB_IMPL

static void R_TRIG_init__(R_TRIG_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->CLK,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->M,__BOOL_LITERAL(FALSE),retain)
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void R_TRIG_body__(R_TRIG_data__ *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,Q,,(__GET_VAR(data__->CLK,) && !(__GET_VAR(data__->M,))));
  __SET_VAR(data__->,M,,__GET_VAR(data__->CLK,));

  goto __end;

__end:
  return;
} // R_TRIG_body__() 
#endif





static void F_TRIG_init__(F_TRIG_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->CLK,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->M,__BOOL_LITERAL(FALSE),retain)
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void F_TRIG_body__(F_TRIG_data__ *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,Q,,(!(__GET_VAR(data__->CLK,)) && !(__GET_VAR(data__->M,))));
  __SET_VAR(data__->,M,,!(__GET_VAR(data__->CLK,)));

  goto __end;

__end:
  return;
} // F_TRIG_body__() 
#endif





static void SR_init__(SR_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->S1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q1,__BOOL_LITERAL(FALSE),retain)
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void SR_body__(SR_data__ *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,Q1,,(__GET_VAR(data__->S1,) || (!(__GET_VAR(data__->R,)) && __GET_VAR(data__->Q1,))));

  goto __end;

__end:
  return;
} // SR_body__() 
#endif





static void RS_init__(RS_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->S,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q1,__BOOL_LITERAL(FALSE),retain)
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void RS_body__(RS_data__ *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,Q1,,(!(__GET_VAR(data__->R1,)) && (__GET_VAR(data__->S,) || __GET_VAR(data__->Q1,))));

  goto __end;

__end:
  return;
} // RS_body__() 
#endif





static void CTU_init__(CTU_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CU_T,retain);
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void CTU_body__(CTU_data__ *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->CU_T.,CLK,,__GET_VAR(data__->CU,));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R,)) {
    __SET_VAR(data__->,CV,,0);
  } else if ((__GET_VAR(data__->CU_T.Q,) && (__GET_VAR(data__->CV,) < __GET_VAR(data__->PV,)))) {
    __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) + 1));
  };
  __SET_VAR(data__->,Q,,(__GET_VAR(data__->CV,) >= __GET_VAR(data__->PV,)));

  goto __end;

__end:
  return;
} // CTU_body__() 
#endif





static void CTU_DINT_init__(CTU_DINT_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CU_T,retain);
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void CTU_DINT_body__(CTU_DINT_data__ *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->CU_T.,CLK,,__GET_VAR(data__->CU,));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R,)) {
    __SET_VAR(data__->,CV,,0);
  } else if ((__GET_VAR(data__->CU_T.Q,) && (__GET_VAR(data__->CV,) < __GET_VAR(data__->PV,)))) {
    __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) + 1));
  };
  __SET_VAR(data__->,Q,,(__GET_VAR(data__->CV,) >= __GET_VAR(data__->PV,)));

  goto __end;

__end:
  return;
} // CTU_DINT_body__() 
#endif





static void CTU_LINT_init__(CTU_LINT_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CU_T,retain);
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void CTU_LINT_body__(CTU_LINT_data__ *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->CU_T.,CLK,,__GET_VAR(data__->CU,));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R,)) {
    __SET_VAR(data__->,CV,,0);
  } else if ((__GET_VAR(data__->CU_T.Q,) && (__GET_VAR(data__->CV,) < __GET_VAR(data__->PV,)))) {
    __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) + 1));
  };
  __SET_VAR(data__->,Q,,(__GET_VAR(data__->CV,) >= __GET_VAR(data__->PV,)));

  goto __end;

__end:
  return;
} // CTU_LINT_body__() 
#endif





static void CTU_UDINT_init__(CTU_UDINT_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CU_T,retain);
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void CTU_UDINT_body__(CTU_UDINT_data__ *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->CU_T.,CLK,,__GET_VAR(data__->CU,));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R,)) {
    __SET_VAR(data__->,CV,,0);
  } else if ((__GET_VAR(data__->CU_T.Q,) && (__GET_VAR(data__->CV,) < __GET_VAR(data__->PV,)))) {
    __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) + 1));
  };
  __SET_VAR(data__->,Q,,(__GET_VAR(data__->CV,) >= __GET_VAR(data__->PV,)));

  goto __end;

__end:
  return;
} // CTU_UDINT_body__() 
#endif





static void CTU_ULINT_init__(CTU_ULINT_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CU_T,retain);
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void CTU_ULINT_body__(CTU_ULINT_data__ *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->CU_T.,CLK,,__GET_VAR(data__->CU,));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R,)) {
    __SET_VAR(data__->,CV,,0);
  } else if ((__GET_VAR(data__->CU_T.Q,) && (__GET_VAR(data__->CV,) < __GET_VAR(data__->PV,)))) {
    __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) + 1));
  };
  __SET_VAR(data__->,Q,,(__GET_VAR(data__->CV,) >= __GET_VAR(data__->PV,)));

  goto __end;

__end:
  return;
} // CTU_ULINT_body__() 
#endif





static void CTD_init__(CTD_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void CTD_body__(CTD_data__ *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->CD_T.,CLK,,__GET_VAR(data__->CD,));
  R_TRIG_body__(&data__->CD_T);
  if (__GET_VAR(data__->LD,)) {
    __SET_VAR(data__->,CV,,__GET_VAR(data__->PV,));
  } else if ((__GET_VAR(data__->CD_T.Q,) && (__GET_VAR(data__->CV,) > 0))) {
    __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) - 1));
  };
  __SET_VAR(data__->,Q,,(__GET_VAR(data__->CV,) <= 0));

  goto __end;

__end:
  return;
} // CTD_body__() 
#endif





static void CTD_DINT_init__(CTD_DINT_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void CTD_DINT_body__(CTD_DINT_data__ *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->CD_T.,CLK,,__GET_VAR(data__->CD,));
  R_TRIG_body__(&data__->CD_T);
  if (__GET_VAR(data__->LD,)) {
    __SET_VAR(data__->,CV,,__GET_VAR(data__->PV,));
  } else if ((__GET_VAR(data__->CD_T.Q,) && (__GET_VAR(data__->CV,) > 0))) {
    __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) - 1));
  };
  __SET_VAR(data__->,Q,,(__GET_VAR(data__->CV,) <= 0));

  goto __end;

__end:
  return;
} // CTD_DINT_body__() 
#endif





static void CTD_LINT_init__(CTD_LINT_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void CTD_LINT_body__(CTD_LINT_data__ *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->CD_T.,CLK,,__GET_VAR(data__->CD,));
  R_TRIG_body__(&data__->CD_T);
  if (__GET_VAR(data__->LD,)) {
    __SET_VAR(data__->,CV,,__GET_VAR(data__->PV,));
  } else if ((__GET_VAR(data__->CD_T.Q,) && (__GET_VAR(data__->CV,) > 0))) {
    __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) - 1));
  };
  __SET_VAR(data__->,Q,,(__GET_VAR(data__->CV,) <= 0));

  goto __end;

__end:
  return;
} // CTD_LINT_body__() 
#endif





static void CTD_UDINT_init__(CTD_UDINT_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void CTD_UDINT_body__(CTD_UDINT_data__ *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->CD_T.,CLK,,__GET_VAR(data__->CD,));
  R_TRIG_body__(&data__->CD_T);
  if (__GET_VAR(data__->LD,)) {
    __SET_VAR(data__->,CV,,__GET_VAR(data__->PV,));
  } else if ((__GET_VAR(data__->CD_T.Q,) && (__GET_VAR(data__->CV,) > 0))) {
    __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) - 1));
  };
  __SET_VAR(data__->,Q,,(__GET_VAR(data__->CV,) <= 0));

  goto __end;

__end:
  return;
} // CTD_UDINT_body__() 
#endif





static void CTD_ULINT_init__(CTD_ULINT_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void CTD_ULINT_body__(CTD_ULINT_data__ *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->CD_T.,CLK,,__GET_VAR(data__->CD,));
  R_TRIG_body__(&data__->CD_T);
  if (__GET_VAR(data__->LD,)) {
    __SET_VAR(data__->,CV,,__GET_VAR(data__->PV,));
  } else if ((__GET_VAR(data__->CD_T.Q,) && (__GET_VAR(data__->CV,) > 0))) {
    __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) - 1));
  };
  __SET_VAR(data__->,Q,,(__GET_VAR(data__->CV,) <= 0));

  goto __end;

__end:
  return;
} // CTD_ULINT_body__() 
#endif





static void CTUD_init__(CTUD_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->QU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->QD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
  R_TRIG_init__(&data__->CU_T,retain);
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void CTUD_body__(CTUD_data__ *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->CD_T.,CLK,,__GET_VAR(data__->CD,));
  R_TRIG_body__(&data__->CD_T);
  __SET_VAR(data__->CU_T.,CLK,,__GET_VAR(data__->CU,));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R,)) {
    __SET_VAR(data__->,CV,,0);
  } else if (__GET_VAR(data__->LD,)) {
    __SET_VAR(data__->,CV,,__GET_VAR(data__->PV,));
  } else {
    if (!((__GET_VAR(data__->CU_T.Q,) && __GET_VAR(data__->CD_T.Q,)))) {
      if ((__GET_VAR(data__->CU_T.Q,) && (__GET_VAR(data__->CV,) < __GET_VAR(data__->PV,)))) {
        __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) + 1));
      } else if ((__GET_VAR(data__->CD_T.Q,) && (__GET_VAR(data__->CV,) > 0))) {
        __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) - 1));
      };
    };
  };
  __SET_VAR(data__->,QU,,(__GET_VAR(data__->CV,) >= __GET_VAR(data__->PV,)));
  __SET_VAR(data__->,QD,,(__GET_VAR(data__->CV,) <= 0));

  goto __end;

__end:
  return;
} // CTUD_body__() 
#endif





static void CTUD_DINT_init__(CTUD_DINT_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->QU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->QD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
  R_TRIG_init__(&data__->CU_T,retain);
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void CTUD_DINT_body__(CTUD_DINT_data__ *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->CD_T.,CLK,,__GET_VAR(data__->CD,));
  R_TRIG_body__(&data__->CD_T);
  __SET_VAR(data__->CU_T.,CLK,,__GET_VAR(data__->CU,));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R,)) {
    __SET_VAR(data__->,CV,,0);
  } else if (__GET_VAR(data__->LD,)) {
    __SET_VAR(data__->,CV,,__GET_VAR(data__->PV,));
  } else {
    if (!((__GET_VAR(data__->CU_T.Q,) && __GET_VAR(data__->CD_T.Q,)))) {
      if ((__GET_VAR(data__->CU_T.Q,) && (__GET_VAR(data__->CV,) < __GET_VAR(data__->PV,)))) {
        __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) + 1));
      } else if ((__GET_VAR(data__->CD_T.Q,) && (__GET_VAR(data__->CV,) > 0))) {
        __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) - 1));
      };
    };
  };
  __SET_VAR(data__->,QU,,(__GET_VAR(data__->CV,) >= __GET_VAR(data__->PV,)));
  __SET_VAR(data__->,QD,,(__GET_VAR(data__->CV,) <= 0));

  goto __end;

__end:
  return;
} // CTUD_DINT_body__() 
#endif





static void CTUD_LINT_init__(CTUD_LINT_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->QU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->QD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
  R_TRIG_init__(&data__->CU_T,retain);
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void CTUD_LINT_body__(CTUD_LINT_data__ *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->CD_T.,CLK,,__GET_VAR(data__->CD,));
  R_TRIG_body__(&data__->CD_T);
  __SET_VAR(data__->CU_T.,CLK,,__GET_VAR(data__->CU,));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R,)) {
    __SET_VAR(data__->,CV,,0);
  } else if (__GET_VAR(data__->LD,)) {
    __SET_VAR(data__->,CV,,__GET_VAR(data__->PV,));
  } else {
    if (!((__GET_VAR(data__->CU_T.Q,) && __GET_VAR(data__->CD_T.Q,)))) {
      if ((__GET_VAR(data__->CU_T.Q,) && (__GET_VAR(data__->CV,) < __GET_VAR(data__->PV,)))) {
        __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) + 1));
      } else if ((__GET_VAR(data__->CD_T.Q,) && (__GET_VAR(data__->CV,) > 0))) {
        __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) - 1));
      };
    };
  };
  __SET_VAR(data__->,QU,,(__GET_VAR(data__->CV,) >= __GET_VAR(data__->PV,)));
  __SET_VAR(data__->,QD,,(__GET_VAR(data__->CV,) <= 0));

  goto __end;

__end:
  return;
} // CTUD_LINT_body__() 
#endif





static void CTUD_UDINT_init__(CTUD_UDINT_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->QU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->QD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
  R_TRIG_init__(&data__->CU_T,retain);
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void CTUD_UDINT_body__(CTUD_UDINT_data__ *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->CD_T.,CLK,,__GET_VAR(data__->CD,));
  R_TRIG_body__(&data__->CD_T);
  __SET_VAR(data__->CU_T.,CLK,,__GET_VAR(data__->CU,));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R,)) {
    __SET_VAR(data__->,CV,,0);
  } else if (__GET_VAR(data__->LD,)) {
    __SET_VAR(data__->,CV,,__GET_VAR(data__->PV,));
  } else {
    if (!((__GET_VAR(data__->CU_T.Q,) && __GET_VAR(data__->CD_T.Q,)))) {
      if ((__GET_VAR(data__->CU_T.Q,) && (__GET_VAR(data__->CV,) < __GET_VAR(data__->PV,)))) {
        __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) + 1));
      } else if ((__GET_VAR(data__->CD_T.Q,) && (__GET_VAR(data__->CV,) > 0))) {
        __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) - 1));
      };
    };
  };
  __SET_VAR(data__->,QU,,(__GET_VAR(data__->CV,) >= __GET_VAR(data__->PV,)));
  __SET_VAR(data__->,QD,,(__GET_VAR(data__->CV,) <= 0));

  goto __end;

__end:
  return;
} // CTUD_UDINT_body__() 
#endif





static void CTUD_ULINT_init__(CTUD_ULINT_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->QU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->QD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
  R_TRIG_init__(&data__->CU_T,retain);
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void CTUD_ULINT_body__(CTUD_ULINT_data__ *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->CD_T.,CLK,,__GET_VAR(data__->CD,));
  R_TRIG_body__(&data__->CD_T);
  __SET_VAR(data__->CU_T.,CLK,,__GET_VAR(data__->CU,));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R,)) {
    __SET_VAR(data__->,CV,,0);
  } else if (__GET_VAR(data__->LD,)) {
    __SET_VAR(data__->,CV,,__GET_VAR(data__->PV,));
  } else {
    if (!((__GET_VAR(data__->CU_T.Q,) && __GET_VAR(data__->CD_T.Q,)))) {
      if ((__GET_VAR(data__->CU_T.Q,) && (__GET_VAR(data__->CV,) < __GET_VAR(data__->PV,)))) {
        __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) + 1));
      } else if ((__GET_VAR(data__->CD_T.Q,) && (__GET_VAR(data__->CV,) > 0))) {
        __SET_VAR(data__->,CV,,(__GET_VAR(data__->CV,) - 1));
      };
    };
  };
  __SET_VAR(data__->,QU,,(__GET_VAR(data__->CV,) >= __GET_VAR(data__->PV,)));
  __SET_VAR(data__->,QD,,(__GET_VAR(data__->CV,) <= 0));

  goto __end;

__end:
  return;
} // CTUD_ULINT_body__() 
#endif





static void TP_init__(TP_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PT,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ET,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->STATE,0,retain)
  __INIT_VAR(data__->PREV_IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CURRENT_TIME,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->START_TIME,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void TP_body__(TP_data__ *data__) {
  // Initialise TEMP variables

  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
__SET_VAR(data__->,CURRENT_TIME,,__CURRENT_TIME)
  #undef GetFbVar
  #undef SetFbVar
;
  if ((((__GET_VAR(data__->STATE,) == 0) && !(__GET_VAR(data__->PREV_IN,))) && __GET_VAR(data__->IN,))) {
    __SET_VAR(data__->,STATE,,1);
    __SET_VAR(data__->,Q,,__BOOL_LITERAL(TRUE));
    __SET_VAR(data__->,START_TIME,,__GET_VAR(data__->CURRENT_TIME,));
  } else if (__GET_VAR(data__->STATE,) == 1) {
    if (___LE_TIME(2, __time_add(__GET_VAR(data__->START_TIME,), __GET_VAR(data__->PT,)), __GET_VAR(data__->CURRENT_TIME,))) {
      __SET_VAR(data__->,STATE,,2);
      __SET_VAR(data__->,Q,,__BOOL_LITERAL(FALSE));
      __SET_VAR(data__->,ET,,__GET_VAR(data__->PT,));
    } else {
      __SET_VAR(data__->,ET,,__time_sub(__GET_VAR(data__->CURRENT_TIME,), __GET_VAR(data__->START_TIME,)));
    };
  };
  if (((__GET_VAR(data__->STATE,) == 2) && !(__GET_VAR(data__->IN,)))) {
    __SET_VAR(data__->,ET,,__time_to_timespec(1, 0, 0, 0, 0, 0));
    __SET_VAR(data__->,STATE,,0);
  };
  __SET_VAR(data__->,PREV_IN,,__GET_VAR(data__->IN,));

  goto __end;

__end:
  return;
} // TP_body__() 
#endif





static void TON_init__(TON_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PT,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ET,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->STATE,0,retain)
  __INIT_VAR(data__->PREV_IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CURRENT_TIME,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->START_TIME,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void TON_body__(TON_data__ *data__) {
  // Initialise TEMP variables

  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
__SET_VAR(data__->,CURRENT_TIME,,__CURRENT_TIME)
  #undef GetFbVar
  #undef SetFbVar
;
  if ((((__GET_VAR(data__->STATE,) == 0) && !(__GET_VAR(data__->PREV_IN,))) && __GET_VAR(data__->IN,))) {
    __SET_VAR(data__->,STATE,,1);
    __SET_VAR(data__->,Q,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,START_TIME,,__GET_VAR(data__->CURRENT_TIME,));
  } else {
    if (!(__GET_VAR(data__->IN,))) {
      __SET_VAR(data__->,ET,,__time_to_timespec(1, 0, 0, 0, 0, 0));
      __SET_VAR(data__->,Q,,__BOOL_LITERAL(FALSE));
      __SET_VAR(data__->,STATE,,0);
    } else if (__GET_VAR(data__->STATE,) == 1) {
      if (___LE_TIME(2, __time_add(__GET_VAR(data__->START_TIME,), __GET_VAR(data__->PT,)), __GET_VAR(data__->CURRENT_TIME,))) {
        __SET_VAR(data__->,STATE,,2);
        __SET_VAR(data__->,Q,,__BOOL_LITERAL(TRUE));
        __SET_VAR(data__->,ET,,__GET_VAR(data__->PT,));
      } else {
        __SET_VAR(data__->,ET,,__time_sub(__GET_VAR(data__->CURRENT_TIME,), __GET_VAR(data__->START_TIME,)));
      };
    };
  };
  __SET_VAR(data__->,PREV_IN,,__GET_VAR(data__->IN,));

  goto __end;

__end:
  return;
} // TON_body__() 
#endif





static void TOF_init__(TOF_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PT,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ET,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->STATE,0,retain)
  __INIT_VAR(data__->PREV_IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CURRENT_TIME,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->START_TIME,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void TOF_body__(TOF_data__ *data__) {
  // Initialise TEMP variables

  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
__SET_VAR(data__->,CURRENT_TIME,,__CURRENT_TIME)
  #undef GetFbVar
  #undef SetFbVar
;
  if ((((__GET_VAR(data__->STATE,) == 0) && __GET_VAR(data__->PREV_IN,)) && !(__GET_VAR(data__->IN,)))) {
    __SET_VAR(data__->,STATE,,1);
    __SET_VAR(data__->,START_TIME,,__GET_VAR(data__->CURRENT_TIME,));
  } else {
    if (__GET_VAR(data__->IN,)) {
      __SET_VAR(data__->,ET,,__time_to_timespec(1, 0, 0, 0, 0, 0));
      __SET_VAR(data__->,STATE,,0);
    } else if (__GET_VAR(data__->STATE,) == 1) {
      if (___LE_TIME(2, __time_add(__GET_VAR(data__->START_TIME,), __GET_VAR(data__->PT,)), __GET_VAR(data__->CURRENT_TIME,))) {
        __SET_VAR(data__->,STATE,,2);
        __SET_VAR(data__->,ET,,__GET_VAR(data__->PT,));
      } else {
        __SET_VAR(data__->,ET,,__time_sub(__GET_VAR(data__->CURRENT_TIME,), __GET_VAR(data__->START_TIME,)));
      };
    };
  };
  __SET_VAR(data__->,Q,,(__GET_VAR(data__->IN,) || (__GET_VAR(data__->STATE,) == 1)));
  __SET_VAR(data__->,PREV_IN,,__GET_VAR(data__->IN,));

  goto __end;

__end:
  return;
} // TOF_body__() 
#endif





static void DERIVATIVE_init__(DERIVATIVE_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->RUN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->XIN,0,retain)
  __INIT_VAR(data__->CYCLE,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->XOUT,0,retain)
  __INIT_VAR(data__->X1,0,retain)
  __INIT_VAR(data__->X2,0,retain)
  __INIT_VAR(data__->X3,0,retain)
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void DERIVATIVE_body__(DERIVATIVE_data__ *data__) {
  // Initialise TEMP variables

  if (__GET_VAR(data__->RUN,)) {
    __SET_VAR(data__->,XOUT,,(((((REAL)3.0 * (__GET_VAR(data__->XIN,) - __GET_VAR(data__->X3,))) + __GET_VAR(data__->X1,)) - __GET_VAR(data__->X2,)) / ((REAL)10.0 * ___TIME_TO_REAL((TIME)__GET_VAR(data__->CYCLE,)))));
    __SET_VAR(data__->,X3,,__GET_VAR(data__->X2,));
    __SET_VAR(data__->,X2,,__GET_VAR(data__->X1,));
    __SET_VAR(data__->,X1,,__GET_VAR(data__->XIN,));
  } else {
    __SET_VAR(data__->,XOUT,,0.0);
    __SET_VAR(data__->,X1,,__GET_VAR(data__->XIN,));
    __SET_VAR(data__->,X2,,__GET_VAR(data__->XIN,));
    __SET_VAR(data__->,X3,,__GET_VAR(data__->XIN,));
  };

  goto __end;

__end:
  return;
} // DERIVATIVE_body__() 
#endif





static void HYSTERESIS_init__(HYSTERESIS_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->XIN1,0,retain)
  __INIT_VAR(data__->XIN2,0,retain)
  __INIT_VAR(data__->EPS,0,retain)
  __INIT_VAR(data__->Q,0,retain)
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void HYSTERESIS_body__(HYSTERESIS_data__ *data__) {
  // Initialise TEMP variables

  if (__GET_VAR(data__->Q,)) {
    if ((__GET_VAR(data__->XIN1,) < (__GET_VAR(data__->XIN2,) - __GET_VAR(data__->EPS,)))) {
      __SET_VAR(data__->,Q,,0);
    };
  } else if ((__GET_VAR(data__->XIN1,) > (__GET_VAR(data__->XIN2,) + __GET_VAR(data__->EPS,)))) {
    __SET_VAR(data__->,Q,,1);
  };

  goto __end;

__end:
  return;
} // HYSTERESIS_body__() 
#endif





static void INTEGRAL_init__(INTEGRAL_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->RUN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->XIN,0,retain)
  __INIT_VAR(data__->X0,0,retain)
  __INIT_VAR(data__->CYCLE,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->XOUT,0,retain)
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void INTEGRAL_body__(INTEGRAL_data__ *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,Q,,!(__GET_VAR(data__->R1,)));
  if (__GET_VAR(data__->R1,)) {
    __SET_VAR(data__->,XOUT,,__GET_VAR(data__->X0,));
  } else if (__GET_VAR(data__->RUN,)) {
    __SET_VAR(data__->,XOUT,,(__GET_VAR(data__->XOUT,) + (__GET_VAR(data__->XIN,) * ___TIME_TO_REAL((TIME)__GET_VAR(data__->CYCLE,)))));
  };

  goto __end;

__end:
  return;
} // INTEGRAL_body__() 
#endif





static void PID_init__(PID_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->AUTO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->SP,0,retain)
  __INIT_VAR(data__->X0,0,retain)
  __INIT_VAR(data__->KP,0,retain)
  __INIT_VAR(data__->TR,0,retain)
  __INIT_VAR(data__->TD,0,retain)
  __INIT_VAR(data__->CYCLE,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->XOUT,0,retain)
  __INIT_VAR(data__->ERROR,0,retain)
  INTEGRAL_init__(&data__->ITERM,retain);
  DERIVATIVE_init__(&data__->DTERM,retain);
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void PID_body__(PID_data__ *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,ERROR,,(__GET_VAR(data__->PV,) - __GET_VAR(data__->SP,)));
  __SET_VAR(data__->ITERM.,RUN,,__GET_VAR(data__->AUTO,));
  __SET_VAR(data__->ITERM.,R1,,!(__GET_VAR(data__->AUTO,)));
  __SET_VAR(data__->ITERM.,XIN,,__GET_VAR(data__->ERROR,));
  __SET_VAR(data__->ITERM.,X0,,(__GET_VAR(data__->TR,) * (__GET_VAR(data__->X0,) - __GET_VAR(data__->ERROR,))));
  __SET_VAR(data__->ITERM.,CYCLE,,__GET_VAR(data__->CYCLE,));
  INTEGRAL_body__(&data__->ITERM);
  __SET_VAR(data__->DTERM.,RUN,,__GET_VAR(data__->AUTO,));
  __SET_VAR(data__->DTERM.,XIN,,__GET_VAR(data__->ERROR,));
  __SET_VAR(data__->DTERM.,CYCLE,,__GET_VAR(data__->CYCLE,));
  DERIVATIVE_body__(&data__->DTERM);
  __SET_VAR(data__->,XOUT,,(__GET_VAR(data__->KP,) * ((__GET_VAR(data__->ERROR,) + (__GET_VAR(data__->ITERM.XOUT,) / __GET_VAR(data__->TR,))) + (__GET_VAR(data__->DTERM.XOUT,) * __GET_VAR(data__->TD,)))));

  goto __end;

__end:
  return;
} // PID_body__() 
#endif





static void RAMP_init__(RAMP_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->RUN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->X0,0,retain)
  __INIT_VAR(data__->X1,0,retain)
  __INIT_VAR(data__->TR,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->CYCLE,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->BUSY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->XOUT,0.0,retain)
  __INIT_VAR(data__->XI,0,retain)
  __INIT_VAR(data__->T,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void RAMP_body__(RAMP_data__ *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,BUSY,,__GET_VAR(data__->RUN,));
  if (__GET_VAR(data__->RUN,)) {
    if (___GE_TIME(2, __GET_VAR(data__->T,), __GET_VAR(data__->TR,))) {
      __SET_VAR(data__->,BUSY,,0);
      __SET_VAR(data__->,XOUT,,__GET_VAR(data__->X1,));
    } else {
      __SET_VAR(data__->,XOUT,,(__GET_VAR(data__->XI,) + (((__GET_VAR(data__->X1,) - __GET_VAR(data__->XI,)) * ___TIME_TO_REAL((TIME)__GET_VAR(data__->T,))) / ___TIME_TO_REAL((TIME)__GET_VAR(data__->TR,)))));
      __SET_VAR(data__->,T,,__time_add(__GET_VAR(data__->T,), __GET_VAR(data__->CYCLE,)));
    };
  } else {
    __SET_VAR(data__->,XOUT,,__GET_VAR(data__->X0,));
    __SET_VAR(data__->,XI,,__GET_VAR(data__->X0,));
    __SET_VAR(data__->,T,,__time_to_timespec(1, 0, 0, 0, 0, 0));
  };

  goto __end;

__end:
  return;
} // RAMP_body__() 
#endif





static void RTC_init__(RTC_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PDT,__dt_to_timespec(0, 0, 0, 1, 1, 1970),retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CDT,__dt_to_timespec(0, 0, 0, 1, 1, 1970),retain)
  __INIT_VAR(data__->PREV_IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OFFSET,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->CURRENT_TIME,__dt_to_timespec(0, 0, 0, 1, 1, 1970),retain)
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void RTC_body__(RTC_data__ *data__) {
  // Initialise TEMP variables

  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
__SET_VAR(data__->,CURRENT_TIME,,__CURRENT_TIME)
  #undef GetFbVar
  #undef SetFbVar
;
  if (__GET_VAR(data__->IN,)) {
    if (!(__GET_VAR(data__->PREV_IN,))) {
      __SET_VAR(data__->,OFFSET,,__time_sub(__GET_VAR(data__->PDT,), __GET_VAR(data__->CURRENT_TIME,)));
    };
    __SET_VAR(data__->,CDT,,__time_add(__GET_VAR(data__->CURRENT_TIME,), __GET_VAR(data__->OFFSET,)));
  } else {
    __SET_VAR(data__->,CDT,,__GET_VAR(data__->CURRENT_TIME,));
  };
  __SET_VAR(data__->,Q,,__GET_VAR(data__->IN,));
  __SET_VAR(data__->,PREV_IN,,__GET_VAR(data__->IN,));

  goto __end;

__end:
  return;
} // RTC_body__() 
#endif





static void SEMA_init__(SEMA_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->CLAIM,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->RELEASE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->BUSY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q_INTERNAL,__BOOL_LITERAL(FALSE),retain)
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void SEMA_body__(SEMA_data__ *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,Q_INTERNAL,,(__GET_VAR(data__->CLAIM,) || (__GET_VAR(data__->Q_INTERNAL,) && !(__GET_VAR(data__->RELEASE,)))));
  __SET_VAR(data__->,BUSY,,__GET_VAR(data__->Q_INTERNAL,));

  goto __end;

__end:
  return;
} // SEMA_body__() 
#endif









#endif //_IEC_STD_FB_IMPL
