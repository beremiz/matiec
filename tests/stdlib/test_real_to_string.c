/*
 * REAL_TO_STRING and LREAL_TO_STRING print as few significant digits as
 * reading the value back needs: 0.1, not 0.100000001 nor 0.10000000000000001.
 * From 6 to 9 for a REAL, from 15 to 17 for an LREAL, and a REAL does not get
 * more digits from the double it goes through. Values are read back with
 * strtof() and strtod(), and must be the same, bit for bit, over the whole
 * range of each type. So must they with STRING_TO_REAL and STRING_TO_LREAL,
 * reading those without dot as integers (16777216) or numbers (1e-30).
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
double iec_lib_strtod(const char *nptr, char **endptr) {return strtod(nptr, endptr);}
float iec_lib_strtof(const char *nptr, char **endptr) {return strtof(nptr, endptr);}

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

  expect("REAL_TO_STRING(0.1)", ___REAL_TO_STRING(1, NULL, 0.1f), "0.1");
  expect("REAL_TO_STRING(100.7)", ___REAL_TO_STRING(1, NULL, 100.7f), "100.7");
  expect("REAL_TO_STRING(1/3)", ___REAL_TO_STRING(1, NULL, 1.0f / 3), "0.33333334");
  expect("REAL_TO_STRING(1.5)", ___REAL_TO_STRING(1, NULL, 1.5f), "1.5");
  expect("REAL_TO_STRING(-2.5)", ___REAL_TO_STRING(1, NULL, -2.5f), "-2.5");
  expect("REAL_TO_STRING(16777216)", ___REAL_TO_STRING(1, NULL, 16777216.0f), "16777216");
  expect("REAL_TO_STRING(1E-30)", ___REAL_TO_STRING(1, NULL, 1e-30f), "1e-30");
  /* (float)strtod() of it is another REAL */
  expect("REAL_TO_STRING(7.038531E-26)", ___REAL_TO_STRING(1, NULL, 7.038531e-26f), "7.038531e-26");
  expect("REAL_TO_STRING(largest)", ___REAL_TO_STRING(1, NULL, real(0x7F7FFFFF)), "3.4028235e+38");
  /* 1e-45 would do, but denormals have fewer digits than FLT_DIG */
  expect("REAL_TO_STRING(smallest)", ___REAL_TO_STRING(1, NULL, real(0x00000001)), "1.4013e-45");

  expect("LREAL_TO_STRING(0.1)", ___LREAL_TO_STRING(1, NULL, 0.1), "0.1");
  expect("LREAL_TO_STRING(6.8)", ___LREAL_TO_STRING(1, NULL, 6.8), "6.8");
  expect("LREAL_TO_STRING(1/3)", ___LREAL_TO_STRING(1, NULL, 1.0 / 3), "0.3333333333333333");
  expect("LREAL_TO_STRING(0.1+0.2)", ___LREAL_TO_STRING(1, NULL, 0.1 + 0.2), "0.30000000000000004");
  expect("LREAL_TO_STRING(1.5)", ___LREAL_TO_STRING(1, NULL, 1.5), "1.5");
  expect("LREAL_TO_STRING(-2.5)", ___LREAL_TO_STRING(1, NULL, -2.5), "-2.5");
  expect("LREAL_TO_STRING(123456789.123456789)", ___LREAL_TO_STRING(1, NULL, 123456789.123456789), "123456789.12345679");
  expect("LREAL_TO_STRING(largest)", ___LREAL_TO_STRING(1, NULL, lreal(0x7FEFFFFFFFFFFFFFULL)), "1.7976931348623157e+308");
  expect("LREAL_TO_STRING(smallest)", ___LREAL_TO_STRING(1, NULL, lreal(1)), "4.94065645841247e-324");

  /* every 4099th REAL, infinities and NaNs excepted */
  for (u = 0; u <= 0xFFFFFFFFULL; u += 4099) {
    REAL x = real((uint32_t)u), back, parsed;
    STRING s;
    if ((u & 0x7F800000) == 0x7F800000) continue;
    s = ___REAL_TO_STRING(1, NULL, x);
    back = strtof(cstring(s, buf), NULL);
    parsed = ___STRING_TO_REAL(1, NULL, s);
    if ((memcmp(&back, &x, sizeof x) != 0 || parsed != x) && mismatches++ < 10)
      printf("REAL_TO_STRING(%.9g) = '%s', read back as %.9g, by STRING_TO_REAL as %.9g\n", x, buf, back, parsed);
  }
  /* 1000000 LREALs spread over the whole range, infinities and NaNs excepted */
  for (i = 0, u = 0; i < 1000000; i++, u += 0x000010C6F7A0B5EDULL) {
    LREAL x = lreal(u), back, parsed;
    STRING s;
    if (((u >> 52) & 0x7FF) == 0x7FF) continue;
    s = ___LREAL_TO_STRING(1, NULL, x);
    back = strtod(cstring(s, buf), NULL);
    parsed = ___STRING_TO_LREAL(1, NULL, s);
    if ((memcmp(&back, &x, sizeof x) != 0 || parsed != x) && mismatches++ < 10)
      printf("LREAL_TO_STRING(%.17g) = '%s', read back as %.17g, by STRING_TO_LREAL as %.17g\n", x, buf, back, parsed);
  }
  if (mismatches) {
    printf("%d values not read back exactly\n", mismatches);
    failures++;
  }

  return failures;
}
