#include "disp.h"

int Displaympv8_t(const mpv8_t *a) {
  int i;

  if (a->sign == true) {
    printf(" + ");
  } else {
    printf(" - ");
  }
  for (i = G_MAIN_DIGIT - 1; i >= 0; i--) {
    printf(" %x ", a->n[i]);
  }
  putchar('\n');

  return 0;
}
