#ifndef main_h
#define main_h
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#define G_MAIN_DIGIT 10
#define G_MAIN_BASE_32 4294967296
#define G_MAIN_BASE_16 65536
#define G_MAIN_BASE_8 256
#define G_MAIN_POSITIVE 1
#define G_MAIN_NEGATIVE -1

typedef struct {
    uint16_t n[G_MAIN_DIGIT];
    bool sign;
}mpv8_t;

#endif /* main_h */
