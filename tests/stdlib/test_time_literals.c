/*
 * TIME, TOD and DT literals, as matiec prints them, with the macros of
 * iec_std_lib.h: seconds are truncated, the nanoseconds of their fraction
 * rounded to the nearest, as T#0.3s is 0.29999999999999999 s, and carried to
 * seconds when they reach 1000000000. Seconds and nanoseconds have the sign
 * of the literal. The macros can initialize a static variable.
 */

#include <stdio.h>
#include "iec_std_lib.h"

TIME __CURRENT_TIME;
BOOL __DEBUG;

static int failures = 0;

static void expect(const char *literal, TIME got, int64_t sec, int32_t nsec) {
  if (got.tv_sec == sec && got.tv_nsec == nsec) return;
  printf("%s: got %lld s %d ns, expected %lld s %d ns\n", literal,
         (long long)got.tv_sec, got.tv_nsec, (long long)sec, nsec);
  failures++;
}

static const TIME initialized = __time_to_timespec(1, 0, 0.3, 0, 0, 0);

int main(void) {
  expect("T#0s", __time_to_timespec(1, 0, 0, 0, 0, 0), 0, 0);
  expect("T#0.3s", __time_to_timespec(1, 0, 0.3, 0, 0, 0), 0, 300000000);
  expect("T#2.675s", __time_to_timespec(1, 0, 2.675, 0, 0, 0), 2, 675000000);
  expect("T#0.7ms", __time_to_timespec(1, 0.7, 0, 0, 0, 0), 0, 700000);
  expect("T#3.5h", __time_to_timespec(1, 0, 0, 0, 3.5, 0), 12600, 0);
  expect("T#1d2h3m4s5.5ms", __time_to_timespec(1, 5.5, 4, 3, 2, 1), 93784, 5500000);
  expect("T#1.9999999999s", __time_to_timespec(1, 0, 1.9999999999, 0, 0, 0), 2, 0);
  expect("T#-2.5s", __time_to_timespec(-1, 0, 2.5, 0, 0, 0), -2, -500000000);
  expect("T#-0.3s", __time_to_timespec(-1, 0, 0.3, 0, 0, 0), 0, -300000000);
  expect("T#-1.9999999999s", __time_to_timespec(-1, 0, 1.9999999999, 0, 0, 0), -2, 0);

  expect("TOD#15:36:55.36", __tod_to_timespec(55.36, 36, 15), 56215, 360000000);
  expect("TOD#23:59:59.9999999999", __tod_to_timespec(59.9999999999, 59, 23), 86400, 0);
  expect("DT#1984-06-25-15:36:55.36", __dt_to_timespec(55.36, 36, 15, 25, 6, 1984), 457025815, 360000000);

  expect("static TIME initialized with T#0.3s", initialized, 0, 300000000);
  return failures;
}
