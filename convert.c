#include "convert.h"

uint64_t convertnumber8_t(mpv8_t *a, int base) {
  int i;
  uint64_t sum = 0;

  for (i = 0; i < G_MAIN_DIGIT; i++) {
    sum += a->n[i] * pow((double)base, (double)i);
  }

  return sum;
}