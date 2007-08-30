#include "iec_std_lib.h"
#include <stdio.h>

/*
 * Functions and variables provied by generated C softPLC
 **/ 
void config_run__(int tick);
void config_init__(void);

/*
 *  Functions and variables to export to generated C softPLC
 **/
 
TIME __CURRENT_TIME;

#define __LOCATED_VAR(type, name, ...) type name;
#include "LOCATED_VARIABLES.h"
#undef __LOCATED_VAR

static int tick = 0;

void run()
{
    printf("Tick %d\n",tick);
    config_run__(tick++);
    printf("  Located variables : \n");
#define __LOCATED_VAR(type, name,...) __print_##type(name);
#include "LOCATED_VARIABLES.h"
#undef __LOCATED_VAR
}

