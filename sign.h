#ifndef sign_h
#define sign_h

#include <stdio.h>
#include "main.h"

int getSign8_t(mpv8_t *p);
void setSign8_t(mpv8_t *p, int s);
void int32_setSign(int32_t p[], int s, int size);
void getAbs8_t(mpv8_t *a, mpv8_t *b);
#endif /* sign_h */
