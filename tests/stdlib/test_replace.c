/*
 * REPLACE(IN1, IN2, L, P), IEC 61131-3 table 34: L characters of IN1, starting
 * at the P-th, are replaced by the whole of IN2 (#41). The result may then be
 * longer than IN1, and is truncated at STR_MAX_LEN without writing past the
 * end of its body (review of #46).
 */

#include <stdio.h>
#include <string.h>
#include "iec_std_lib.h"

TIME __CURRENT_TIME;
BOOL __DEBUG;

static int failures = 0;

static STRING str(const char *s) {
  STRING r = __INIT_STRING;
  r.len = strlen(s);
  memcpy(r.body, s, r.len);
  return r;
}

static STRING repeat(char c, int n) {
  STRING r = __INIT_STRING;
  memset(r.body, c, n);
  r.len = n;
  return r;
}

static void expect(const char *what, STRING got, STRING want) {
  if (got.len == want.len && memcmp(got.body, want.body, got.len) == 0) return;
  printf("%s: got '%.*s' (%d), expected '%.*s' (%d)\n", what,
         got.len, (char *)got.body, got.len, want.len, (char *)want.body, want.len);
  failures++;
}

int main(void) {
  STRING full = __INIT_STRING;

  /* IN2 longer, as long as and shorter than the L characters it replaces */
  expect("REPLACE('hello', 'YY', 1, 2)", __replace(str("hello"), str("YY"), 1, 2), str("hYYllo"));
  expect("REPLACE('hello', 'YY', 2, 2)", __replace(str("hello"), str("YY"), 2, 2), str("hYYlo"));
  expect("REPLACE('hello', 'YY', 3, 2)", __replace(str("hello"), str("YY"), 3, 2), str("hYYo"));
  expect("REPLACE('hello', 'YY', 4, 2)", __replace(str("hello"), str("YY"), 4, 2), str("hYY"));
  expect("REPLACE('hello', '', 2, 2)",   __replace(str("hello"), str(""), 2, 2),   str("hlo"));
  expect("REPLACE('hello', 'YY', 0, 1)", __replace(str("hello"), str("YY"), 0, 1), str("YYhello"));

  /* a result longer than STR_MAX_LEN is truncated: 'a', the 100 'b', then 'a' up to the end */
  full = repeat('a', STR_MAX_LEN);
  memset(&full.body[1], 'b', 100);
  expect("REPLACE(120 'a', 100 'b', 1, 2)",
         __replace(repeat('a', 120), repeat('b', 100), 1, 2), full);

  /* IN2 alone fills the result, nothing of the rest of IN1 fits */
  full = repeat('c', STR_MAX_LEN);
  full.body[0] = 'a';
  expect("REPLACE(120 'a', STR_MAX_LEN 'c', 1, 2)",
         __replace(repeat('a', 120), repeat('c', STR_MAX_LEN), 1, 2), full);

  return failures != 0;
}
