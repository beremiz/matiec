/*
 * Extensible functions (ADD, MUL, AND, OR, XOR, MAX, MIN, comparisons, MUX,
 * CONCAT) get their operands through "...", read with va_arg() as their
 * VA_ARGS_<type>. They are called here as the generated C code calls them,
 * with operands cast to that type. Results are computed in the operands' type,
 * as REAL additions rounded to float at each step, or SINT products wrapped.
 */

#include <stdio.h>
#include <string.h>
#include "iec_std_lib.h"

TIME __CURRENT_TIME;
BOOL __DEBUG;

static int failures = 0;

static void expect(const char *what, int ok) {
  if (ok) return;
  printf("%s: wrong result\n", what);
  failures++;
}

static STRING str(const char *s) {
  STRING r = __INIT_STRING;
  r.len = strlen(s);
  memcpy(r.body, s, r.len);
  return r;
}

static int str_eq(STRING a, const char *b) {
  return a.len == strlen(b) && memcmp(a.body, b, a.len) == 0;
}

#define R(x) (VA_ARGS_REAL)(REAL)(x)
#define S(x) (VA_ARGS_SINT)(SINT)(x)
#define I(x) (VA_ARGS_INT)(INT)(x)
#define B(x) (VA_ARGS_BOOL)(BOOL)(x)
#define BY(x) (VA_ARGS_BYTE)(BYTE)(x)

int main(void) {
  BOOL eno;
  REAL want;
  TIME t1 = {1, 0}, t2 = {2, 0};

  want = 0.1f; want += 0.2f; want += 0.3f;
  expect("ADD(REAL#0.1, 0.2, 0.3)", ___ADD__REAL__REAL(1, NULL, 3, R(0.1f), R(0.2f), R(0.3f)) == want);
  expect("ADD(INT#-1, -2, 5)", ___ADD__INT__INT(1, NULL, 3, I(-1), I(-2), I(5)) == 2);
  expect("MUL(SINT#100, 2, 3)", ___MUL__SINT__SINT(1, NULL, 3, S(100), S(2), S(3)) == (SINT)((SINT)(100 * 2) * 3));
  expect("ADD(LREAL#1.5, 2.25)", ___ADD__LREAL__LREAL(1, NULL, 2, (VA_ARGS_LREAL)1.5, (VA_ARGS_LREAL)2.25) == 3.75);

  expect("AND(TRUE, TRUE, FALSE)", ___AND__BOOL__BOOL(1, NULL, 3, B(1), B(1), B(0)) == 0);
  expect("AND(TRUE, TRUE)", ___AND__BOOL__BOOL(1, NULL, 2, B(1), B(1)) == 1);
  expect("OR(FALSE, FALSE, TRUE)", ___OR__BOOL__BOOL(1, NULL, 3, B(0), B(0), B(1)) == 1);
  expect("XOR(TRUE, TRUE, TRUE)", ___XOR__BOOL__BOOL(1, NULL, 3, B(1), B(1), B(1)) == 1);
  expect("XOR(TRUE, TRUE)", ___XOR__BOOL__BOOL(1, NULL, 2, B(1), B(1)) == 0);
  expect("AND(16#F0, 16#3C, 16#FF)", ___AND__BYTE__BYTE(1, NULL, 3, BY(0xF0), BY(0x3C), BY(0xFF)) == 0x30);

  expect("MAX(REAL#1.5, -2.0, 3.25)", ___MAX__REAL__REAL(1, NULL, 3, R(1.5f), R(-2.0f), R(3.25f)) == 3.25f);
  expect("MIN(SINT#5, -7, 3)", ___MIN__SINT__SINT(1, NULL, 3, S(5), S(-7), S(3)) == -7);
  expect("MAX('ab', 'b', 'a')", str_eq(___MAX__STRING__STRING(1, NULL, 3, str("ab"), str("b"), str("a")), "b"));
  expect("MAX(T#1s, T#2s)", ___MAX__TIME__TIME(1, NULL, 2, t1, t2).tv_sec == 2);

  expect("GT(INT#3, 2, 1)", ___GT__BOOL__INT(1, NULL, 3, I(3), I(2), I(1)) == 1);
  expect("GT(INT#3, 2, 2)", ___GT__BOOL__INT(1, NULL, 3, I(3), I(2), I(2)) == 0);
  expect("EQ(REAL#0.5, 0.5, 0.5)", ___EQ__BOOL__REAL(1, NULL, 3, R(0.5f), R(0.5f), R(0.5f)) == 1);
  expect("LT(T#1s, T#2s)", ___LT__BOOL__TIME(1, NULL, 2, t1, t2) == 1);
  expect("GE(SINT#-1, -1, -2)", ___GE__BOOL__SINT(1, NULL, 3, S(-1), S(-1), S(-2)) == 1);

  expect("MUX(1, REAL#1.0, 2.0, 3.0)", ___MUX__REAL__INT__REAL(1, &eno, 1, 3, R(1.0f), R(2.0f), R(3.0f)) == 2.0f && eno);
  expect("MUX(0, SINT#-5, 6)", ___MUX__SINT__USINT__SINT(1, &eno, 0, 2, S(-5), S(6)) == -5 && eno);
  /* K out of range, negative K included, gives the type's initial value and ENO FALSE */
  expect("MUX(3, REAL#1.0, 2.0, 3.0)", ___MUX__REAL__INT__REAL(1, &eno, 3, 3, R(1.0f), R(2.0f), R(3.0f)) == 0.0f && !eno);
  expect("MUX(-1, REAL#1.0, 2.0, 3.0)", ___MUX__REAL__INT__REAL(1, &eno, -1, 3, R(1.0f), R(2.0f), R(3.0f)) == 0.0f && !eno);

  expect("CONCAT('ab', 'c', 'de')", str_eq(___CONCAT(1, NULL, 3, str("ab"), str("c"), str("de")), "abcde"));

  /* EN FALSE: nothing is read, ENO is FALSE */
  expect("ADD(EN := FALSE, INT#1, 2)", ___ADD__INT__INT(0, &eno, 2, I(1), I(2)) == 0 && !eno);
  expect("ADD(EN := TRUE, INT#1, 2)", ___ADD__INT__INT(1, &eno, 2, I(1), I(2)) == 3 && eno);

  return failures;
}
