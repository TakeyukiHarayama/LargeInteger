#include "comp.h"
#include "sign.h"

//多倍長の大小比較 a>b : 1, a<b : -1, エラー時は2
int numComp8_t(mpv8_t *a, mpv8_t *b) {
  int i;
  int getSigna = getSign8_t(a);
  int getSignb = getSign8_t(b);

  if (getSigna > getSignb) {
    return 1;
  }
  if (getSigna < getSignb) {
    return -1;
  }
  // a,b共に正のとき
  if (getSigna == 1 || getSignb == 1) {
    for (i = G_MAIN_DIGIT - 1; i >= 0; i--) {
      if (a->n[i] > b->n[i]) {
        return 1;
      }
      if (b->n[i] > a->n[i]) {
        return -1;
      }
    }
  }
  // a,b共に負のとき
  if (getSigna == -1 || getSignb == -1) {
    int i;
    for (i = G_MAIN_DIGIT - 1; i >= 0; i--) {
      if (a->n[i] > b->n[i]) {
        return -1;
      }
      if (b->n[i] > a->n[i]) {
        return 1;
      }
    }
  }
  return 2;
}
