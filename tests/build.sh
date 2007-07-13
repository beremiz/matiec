#!/bin/bash

../iec2cc STD_TEST.st -I ../lib

gcc -I ../lib -c -g STD_RESSOURCE.c

gcc -I ../lib -c  -g STD_CONF.c

gcc -I ../lib main.c STD_CONF.o STD_RESSOURCE.o -g -l rt -o test
