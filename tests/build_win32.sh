#!/bin/bash

STFILE=$1

shift

CFLAGS=$*


#CC=gcc
CC=i686-mingw32-gcc

../iec2c $STFILE -I ../lib 
#2>/dev/null

$CC -I ../lib -c STD_RESSOURCE.c $CFLAGS

$CC -I ../lib -c  STD_CONF.c $CFLAGS

$CC -I ../lib -c  plc.c $CFLAGS

$CC -I ../lib main.c STD_CONF.o STD_RESSOURCE.o plc.o $CFLAGS -o test.exe
