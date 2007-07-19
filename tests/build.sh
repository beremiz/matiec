#!/bin/bash

STFILE=$1

shift

CFLAGS=$*

../iec2cc $STFILE -I ../lib 
#2>/dev/null

gcc -I ../lib -c STD_RESSOURCE.c $CFLAGS

gcc -I ../lib -c  STD_CONF.c $CFLAGS

gcc -I ../lib main.c STD_CONF.o STD_RESSOURCE.o $CFLAGS -l rt -o test
