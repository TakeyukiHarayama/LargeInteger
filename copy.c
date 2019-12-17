#include "copy.h"
#include "clear.h"

//多倍長aをbにコピーする
void copympv8_t(mpv8_t *a, mpv8_t *b) {
  int i;

  clearByZero8_t(b);
  b->sign = a->sign;
  for (i = 0; i < G_MAIN_DIGIT; i++) {
    b->n[i] = a->n[i];
  }
}
