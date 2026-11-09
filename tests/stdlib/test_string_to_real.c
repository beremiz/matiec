/*
 * STRING_TO_REAL and STRING_TO_LREAL of numbers with no digit before their
 * dot, as of integers and of numbers with REAL# prefix. Of exponents, with or
 * without dot, but not in digits of hexadecimal integers, of '_' separators,
 * and of more decimals than an int holds. STRING_TO_LREAL keeps the precision
 * of an LREAL, STRING_TO_REAL gives the REAL nearest to the number, which a
 * REAL of the nearest LREAL is not always.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iec_std_lib.h"

TIME __CURRENT_TIME;
BOOL __DEBUG;

double iec_lib_strtod(const char *nptr, char **endptr) {return strtod(nptr, endptr);}
float iec_lib_strtof(const char *nptr, char **endptr) {return strtof(nptr, endptr);}

static int failures = 0;

static STRING str(const char *s) {
  STRING r = __INIT_STRING;
  r.len = strlen(s);
  memcpy(r.body, s, r.len);
  return r;
}

static void expect(const char *what, LREAL got, LREAL want) {
  if (got == want) return;
  printf("%s: got %.17g, expected %.17g\n", what, got, want);
  failures++;
}

int main(void) {
  expect("STRING_TO_REAL('42')", ___STRING_TO_REAL(1, NULL, str("42")), 42.0f);
  expect("STRING_TO_REAL('1.5')", ___STRING_TO_REAL(1, NULL, str("1.5")), 1.5f);
  expect("STRING_TO_REAL('.5')", ___STRING_TO_REAL(1, NULL, str(".5")), 0.5f);
  expect("STRING_TO_REAL('-.5')", ___STRING_TO_REAL(1, NULL, str("-.5")), -0.5f);
  expect("STRING_TO_REAL('REAL#.25')", ___STRING_TO_REAL(1, NULL, str("REAL#.25")), 0.25f);
  expect("STRING_TO_LREAL('.5')", ___STRING_TO_LREAL(1, NULL, str(".5")), 0.5);

  expect("STRING_TO_REAL('1.5E3')", ___STRING_TO_REAL(1, NULL, str("1.5E3")), 1500.0f);
  expect("STRING_TO_REAL('1.5e3')", ___STRING_TO_REAL(1, NULL, str("1.5e3")), 1500.0f);
  expect("STRING_TO_REAL('1e-30')", ___STRING_TO_REAL(1, NULL, str("1e-30")), 1e-30f);
  expect("STRING_TO_REAL('-2E+20')", ___STRING_TO_REAL(1, NULL, str("-2E+20")), -2e20f);
  expect("STRING_TO_REAL('16#1E')", ___STRING_TO_REAL(1, NULL, str("16#1E")), 30.0f);
  expect("STRING_TO_REAL('1_000.25')", ___STRING_TO_REAL(1, NULL, str("1_000.25")), 1000.25f);
  expect("STRING_TO_REAL('0.1')", ___STRING_TO_REAL(1, NULL, str("0.1")), 0.1f);
  expect("STRING_TO_REAL('7.038531e-26')", ___STRING_TO_REAL(1, NULL, str("7.038531e-26")), 7.038531e-26f);
  expect("STRING_TO_LREAL('0.1')", ___STRING_TO_LREAL(1, NULL, str("0.1")), 0.1);
  expect("STRING_TO_LREAL('6.8')", ___STRING_TO_LREAL(1, NULL, str("6.8")), 6.8);
  expect("STRING_TO_LREAL('2.5E-12')", ___STRING_TO_LREAL(1, NULL, str("2.5E-12")), 2.5e-12);
  expect("STRING_TO_LREAL('1.7976931348623157e+308')",
         ___STRING_TO_LREAL(1, NULL, str("1.7976931348623157e+308")), 1.7976931348623157e+308);
  expect("STRING_TO_LREAL('0.1234567890123')", ___STRING_TO_LREAL(1, NULL, str("0.1234567890123")), 0.1234567890123);
  expect("STRING_TO_LREAL('LREAL#-1_234.5E-1')", ___STRING_TO_LREAL(1, NULL, str("LREAL#-1_234.5E-1")), -123.45);
  return failures;
}
