#!/bin/bash

CFLAGS=$*

../iec2cc STD_TEST.st -I ../lib 
#2>/dev/null

gcc -I ../lib -c STD_RESSOURCE.c $CFLAGS

gcc -I ../lib -c  STD_CONF.c $CFLAGS

gcc -I ../lib main.c STD_CONF.o STD_RESSOURCE.o $CFLAGS -l rt -o test
