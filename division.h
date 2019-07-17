#ifndef division_h
#define division_h

#include <stdio.h>
#include "main.h"

int nlz8(uint8_t x);
int nlz16(uint16_t x);
int KNUTH_div(mpv_t *u, mpv_t *v, mpv_t *q, mpv_t *r, int const m, int const n, int  base);
int KNUTH_div8_t(mpv8_t *u, mpv8_t *v, mpv8_t *q, mpv8_t *r, int const m, int const n, int  base);
#endif /* division_h */
