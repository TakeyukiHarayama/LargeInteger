#ifndef Structure_h
#define Structure_h
#include <stdbool.h>
#include <stdint.h>
#include<stdlib.h>
#include <math.h>
#define DIGIT 10

typedef struct {
    uint16_t n[DIGIT];
    bool sign;
}mpv_t;

typedef struct {
    uint16_t n[DIGIT];
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
int KNUTH_numComp(uint16_t a[], uint16_t b[], int size);
//int型変数のセット
int setInt(mpv_t *a, uint64_t x, int base);
int setInt8_t(mpv8_t *a, uint64_t x, int base);
uint64_t convertnumber8_t(mpv8_t *a, int base);
uint64_t convertnumber(mpv_t *a, int base);

int add8_t(mpv8_t *a, mpv8_t *b,mpv8_t *c, int din, int base);
int add(mpv_t *a, mpv_t *b,mpv_t *c, int din, int base);
int sub8_t(mpv8_t *a, mpv8_t *b, mpv8_t *c, int din, int base);
int sub(mpv_t *a, mpv_t *b, mpv_t *c, int din, int base);
int Knuth_multiple_sub(uint16_t a[], uint16_t b[], int32_t c[], int base, int size);
int BasecaseMultiply(mpv_t *a, mpv_t *b, mpv_t *c, int n, int m, int base);
int nlz8(uint8_t x);
int nlz16(uint16_t x);
int KNUTH_div(mpv_t *u, mpv_t *v, mpv_t *q, mpv_t *r, int const m, int const n, int  base);
int KNUTH_div8_t(mpv8_t *u, mpv8_t *v, mpv8_t *q, mpv8_t *r, int const m, int const n, int  base);
#endif /* Structure_h */
