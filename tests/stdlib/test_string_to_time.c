/*
 * STRING_TO_TIME of a number of seconds keeps its fraction, rounded to the
 * nearest nanosecond, as decimal fractions are not exact in an LREAL. Like
 * negative TIME literals, a negative time has negative seconds and
 * nanoseconds.
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

static void expect(const char *in, int64_t sec, int32_t nsec) {
  TIME got = ___STRING_TO_TIME(1, NULL, str(in));
  if (got.tv_sec == sec && got.tv_nsec == nsec) return;
  printf("STRING_TO_TIME('%s'): got %lld s %d ns, expected %lld s %d ns\n", in,
         (long long)got.tv_sec, got.tv_nsec, (long long)sec, nsec);
  failures++;
}

int main(void) {
  expect("42", 42, 0);
  expect("1.5", 1, 500000000);
  expect("0.3", 0, 300000000);
  expect("2.675", 2, 675000000);
  expect("0.123456789", 0, 123456789);
  expect("0.000000001", 0, 1);
  expect("86400.25", 86400, 250000000);
  expect("-1.25", -1, -250000000);
  expect("-0.3", 0, -300000000);
  return failures;
}
