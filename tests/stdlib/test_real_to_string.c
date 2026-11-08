/*
 * REAL_TO_STRING and LREAL_TO_STRING print as many significant digits as
 * reading any value back exactly may need, 9 for a REAL and 17 for an LREAL,
 * and a REAL does not get more digits from the double it goes through.
 * Values are read back with strtof() and strtod(), and must be the same,
 * bit for bit, over the whole range of each type.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include "iec_std_lib.h"

TIME __CURRENT_TIME;
BOOL __DEBUG;

int iec_lib_snprintf(char *s, size_t maxlen, const char *format, ...) {
  va_list ap;
  int ret;
  va_start(ap, format);
  ret = vsnprintf(s, maxlen, format, ap);
  va_end(ap);
  return ret;
}

static int failures = 0;

static void expect(const char *what, STRING got, const char *want) {
  if (got.len == strlen(want) && memcmp(got.body, want, got.len) == 0) return;
  printf("%s: got '%.*s', expected '%s'\n", what, got.len, (char *)got.body, want);
  failures++;
}

static char *cstring(STRING s, char *buf) {
  memcpy(buf, s.body, s.len);
  buf[s.len] = '\0';
  return buf;
}

static REAL real(uint32_t bits) {REAL r; memcpy(&r, &bits, sizeof r); return r;}
static LREAL lreal(uint64_t bits) {LREAL r; memcpy(&r, &bits, sizeof r); return r;}

int main(void) {
  char buf[STR_MAX_LEN + 1];
  uint64_t u;
  int i, mismatches = 0;

  expect("REAL_TO_STRING(0.1)", ___REAL_TO_STRING(1, NULL, 0.1f), "0.100000001");
  expect("REAL_TO_STRING(100.7)", ___REAL_TO_STRING(1, NULL, 100.7f), "100.699997");
  expect("REAL_TO_STRING(1.5)", ___REAL_TO_STRING(1, NULL, 1.5f), "1.5");
  expect("REAL_TO_STRING(-2.5)", ___REAL_TO_STRING(1, NULL, -2.5f), "-2.5");
  expect("REAL_TO_STRING(16777216)", ___REAL_TO_STRING(1, NULL, 16777216.0f), "16777216");
  expect("REAL_TO_STRING(1E-30)", ___REAL_TO_STRING(1, NULL, 1e-30f), "1e-30");
  expect("REAL_TO_STRING(largest)", ___REAL_TO_STRING(1, NULL, real(0x7F7FFFFF)), "3.40282347e+38");
  expect("REAL_TO_STRING(smallest)", ___REAL_TO_STRING(1, NULL, real(0x00000001)), "1.40129846e-45");

  expect("LREAL_TO_STRING(0.1)", ___LREAL_TO_STRING(1, NULL, 0.1), "0.10000000000000001");
  expect("LREAL_TO_STRING(1.5)", ___LREAL_TO_STRING(1, NULL, 1.5), "1.5");
  expect("LREAL_TO_STRING(-2.5)", ___LREAL_TO_STRING(1, NULL, -2.5), "-2.5");
  expect("LREAL_TO_STRING(123456789.123456789)", ___LREAL_TO_STRING(1, NULL, 123456789.123456789), "123456789.12345679");
  expect("LREAL_TO_STRING(largest)", ___LREAL_TO_STRING(1, NULL, lreal(0x7FEFFFFFFFFFFFFFULL)), "1.7976931348623157e+308");
  expect("LREAL_TO_STRING(smallest)", ___LREAL_TO_STRING(1, NULL, lreal(1)), "4.9406564584124654e-324");

  /* every 4099th REAL, infinities and NaNs excepted */
  for (u = 0; u <= 0xFFFFFFFFULL; u += 4099) {
    REAL x = real((uint32_t)u), back;
    if ((u & 0x7F800000) == 0x7F800000) continue;
    back = strtof(cstring(___REAL_TO_STRING(1, NULL, x), buf), NULL);
    if (memcmp(&back, &x, sizeof x) != 0 && mismatches++ < 10)
      printf("REAL_TO_STRING(%.9g) = '%s', read back as %.9g\n", x, buf, back);
  }
  /* 1000000 LREALs spread over the whole range, infinities and NaNs excepted */
  for (i = 0, u = 0; i < 1000000; i++, u += 0x000010C6F7A0B5EDULL) {
    LREAL x = lreal(u), back;
    if (((u >> 52) & 0x7FF) == 0x7FF) continue;
    back = strtod(cstring(___LREAL_TO_STRING(1, NULL, x), buf), NULL);
    if (memcmp(&back, &x, sizeof x) != 0 && mismatches++ < 10)
      printf("LREAL_TO_STRING(%.17g) = '%s', read back as %.17g\n", x, buf, back);
  }
  if (mismatches) {
    printf("%d values not read back exactly\n", mismatches);
    failures++;
  }

  return failures;
}
