#include "sign.h"
#include "clear.h"
#include "copy.h"

//多倍長変数pの符号が正なら+1を、負なら-1を返す
int getSign8_t(mpv8_t *p) {
  if (p->sign == true) {
    return 1;
  } else if (p->sign == false) {
    return -1;
  }
  return 0;
}

//多倍長変数pの符号をs = 1なら正に、s = -1なら負に設定する
void setSign8_t(mpv8_t *p, int s) {
  if (s == 1) {
    p->sign = true;
  } else {
    p->sign = false;
  }
}

//多倍長aの絶対値をbにセットする
void getAbs8_t(mpv8_t *a, mpv8_t *b) {
  copympv8_t(a, b);
  setSign8_t(b, 1);
}

//符号をs = 1なら正に、s = -1なら負に設定する
void int32_setSign(int32_t p[], int s, int size) {
  int i;
  int top = -1;

  for (i = size - 1; i >= 0; i++) {
    if (p[i] != 0) {
      top = i;
      break;
    }
  }
  if (top == -1) {
    printf("int32_setSign error!\n");
    exit(1);
  }
  if (s == -1) {
    p[top] *= -1;
  }
}
