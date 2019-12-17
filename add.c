#include "add.h"
#include "sign.h"
#include "sub.h"

// a+b=c
int add8_t(mpv8_t *a, mpv8_t *b, mpv8_t *c, int din, int base) {
  int i = 0;
  long long s = 0;
  int d = 0;
  int getSigna = getSign8_t(a);
  int getSignb = getSign8_t(b);
  bool SignFlag = true;
  mpv8_t absab;

  // aが正でbが負
  if (getSigna == G_MAIN_POSITIVE && getSignb == G_MAIN_NEGATIVE) {
    getAbs8_t(b, &absab);
    return sub8_t(a, &absab, c, din, base);
    ;
  }
  // aが負でbが正
  if (getSigna == G_MAIN_NEGATIVE && getSignb == G_MAIN_POSITIVE) {
    getAbs8_t(a, &absab);
    return sub8_t(b, &absab, c, din, base);
  }
  // aが負でbも負
  if (getSigna == G_MAIN_NEGATIVE && getSignb == G_MAIN_NEGATIVE) {
    SignFlag = false;
  }
  // aが正でbも正
  if (getSigna == G_MAIN_POSITIVE && getSignb == G_MAIN_POSITIVE) {
    SignFlag = true;
  }

  d = din;
  for (i = 0; i < G_MAIN_DIGIT; i++) {
    s = a->n[i] + b->n[i] + d;
    d = s / base;
    c->n[i] = s % base;
  }
  if (SignFlag == false) {
    setSign8_t(c, G_MAIN_NEGATIVE);
  }
  return d;
}
