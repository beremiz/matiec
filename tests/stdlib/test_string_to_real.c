/*
 * STRING_TO_REAL and STRING_TO_LREAL of numbers with no digit before their
 * dot, as of integers and of numbers with REAL# prefix.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iec_std_lib.h"

TIME __CURRENT_TIME;
BOOL __DEBUG;

/* only called for an exponent, none of the strings below has one */
double iec_lib_pow(double x, double y) {abort();}

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
  return failures;
}
