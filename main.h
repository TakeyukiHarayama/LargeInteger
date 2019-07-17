#ifndef Structure_h
#define Structure_h
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
}mpv_t;

typedef struct {
    uint16_t n[G_MAIN_DIGIT];
    bool sign;
}mpv8_t;

int clearByZero(mpv_t *a);
int clearByZero8_t(mpv8_t *a);
int Displaympv8_t(const mpv8_t *a);
int Displaympv_t(const mpv_t *a);
//多倍長変数pの符号が正なら+1を、負なら-1を返す
int getSign(mpv_t *p);
int getSign8_t(mpv8_t *p);
//多倍長変数pの符号をs = 1なら正に、s = -1なら負に設定する
void setSign(mpv_t *p, int s);
void setSign8_t(mpv8_t *p, int s);
void int32_setSign(int32_t p[], int s, int size);
//多倍長aの絶対値をbにセットする
void getAbs(mpv_t *a, mpv_t *b);
void getAbs8_t(mpv8_t *a, mpv8_t *b);
//多倍長aの符号以外をbにコピーする
void copympv_t(mpv_t *a, mpv_t *b);
void copympv8_t(mpv8_t *a, mpv8_t *b);
//多倍長の大小比較 a>b : 1, a<b : -1, エラー時は2
int numComp8_t(mpv8_t *a, mpv8_t *b);
int numComp(mpv_t *a, mpv_t *b);
//int型変数のセット
int setInt(mpv_t *a, int x, int base);
int setInt8_t(mpv8_t *a, int x, int base);
uint64_t convertnumber8_t(mpv8_t *a, int base);
uint64_t convertnumber(mpv_t *a, int base);
#endif /* Structure_h */
