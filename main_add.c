#include<stdio.h>
#include<stdbool.h>
#include "main.h"

#define BIT32 4294967295

int main(void){
	uint64_t i, j;
	uint64_t checknumber, correctnumber;
	mpv_t a, b, c, q, r;
	int LengthOfa = 0;
	int LengthOfb= 0;
	//int LengthOfc = DIGIT-1;
	int din = 0;
	//int dout = 0;
	int base = 65536;

	clearByZero(&a);
	clearByZero(&b);
	clearByZero(&c);
	clearByZero(&q);
	clearByZero(&r);



	for(i=2; i<=BIT32; i++){
		for(j=0; j<=BIT32; j++){
			LengthOfa = setInt(&a, i, base);
			LengthOfb = setInt(&b, j, base);
			add(&a, &b, &c, din, base);
			checknumber = convertnumber(&c, base);
			correctnumber = i + j;
			if(checknumber != correctnumber){
				printf("Error. wrong answer\n");
				printf("a   ");
				Displaympv_t(&a);
				printf("b   ");
				Displaympv_t(&b);
				printf("c   ");
				Displaympv_t(&c);
				printf("correct answer is %llu\n", correctnumber);
				exit(1);
			}
			if((j % 10000000) == 0){printf("%llu + %llu ok\n", i, j);};
		}
	}

	/*
	   printf("add ");
	   Displaympv_t(&c);
	   printf("sub ");
	   sub(&a, &b, &c, din, base);
	   Displaympv_t(&c);
	   BasecaseMultiply(&a, &b, &c, LengthOfa, LengthOfb, base);
	   printf("mul ");
	   Displaympv_t(&c);
	   KNUTH_div(&a, &b, &q, &r, LengthOfa, LengthOfb, base);
	   printf("divq");
	   Displaympv_t(&q);
	   printf("divr");
	   Displaympv_t(&r);
	   */

	return 0;
}

int clearByZero(mpv_t *a){
	int i;

	a->sign = true;
	for(i=0; i<DIGIT; i++){
		a->n[i] = 0;
	}

	return 0;
}

int Displaympv_t(const mpv_t *a){
	int i;

	if(a->sign == true){
		printf(" + ");
	}else{
		printf(" - ");
	}
	for(i=DIGIT-1; i>=0; i--){
		printf(" %hu ", a->n[i]);
	}
	putchar('\n');

	return 0;
}

//多倍長変数pの符号が正なら+1を、負なら-1を返す
int getSign(mpv_t *p){
	if(p->sign == true){
		return 1;
	}else if(p->sign == false){
		return -1;
	}
	return 0;
}

//多倍長変数pの符号をs = 1なら正に、s = -1なら負に設定する
void setSign(mpv_t *p, int s){
	if(s == 1){
		p->sign = true;
	}else{
		p->sign = false;
	}
}
//符号をs = 1なら正に、s = -1なら負に設定する
void int32_setSign(int32_t p[], int s, int size){
	int i;
	int top = -1;

	for (i=size-1; i >=0; i++) {
		if(p[i] != 0){
			top = i;
			break;
		}
	}
	if(top == -1){
		printf("int32_setSign error!\n");
		exit(1);
	}
	if(s == -1){
		p[top] *= -1;
	}
}

//多倍長aの絶対値をbにセットする
void getAbs(mpv_t *a, mpv_t *b){
	copympv_t(a, b);
	setSign(b, 1);
}

//多倍長aをbにコピーする
void copympv_t(mpv_t *a, mpv_t *b)
{
	int i;

	clearByZero(b);
	b->sign = a->sign;
	for(i = 0; i < DIGIT; i++){
		b->n[i] = a->n[i];
	}
}

//多倍長の大小比較 a>b : 1, a<b : -1, エラー時は2
int numComp(mpv_t *a, mpv_t *b){
	int i;
	int getSigna = getSign(a);
	int getSignb = getSign(b);

	if(getSigna > getSignb ){
		return 1;
	}
	if(getSigna < getSignb ){
		return -1;
	}
	//a,b共に正のとき
	if(getSigna == 1 || getSignb == 1){
		for(i = DIGIT-1; i>= 0; i--){
			if(a->n[i] > b->n[i]){
				return 1;
			}
			if(b->n[i] > a->n[i]){
				return -1;
			}
		}
	}
	//a,b共に負のとき
	if(getSigna == -1 || getSignb == -1){
		int i;
		for(i = DIGIT-1; i>= 0; i--){
			if(a->n[i] > b->n[i]){
				return -1;
			}
			if(b->n[i] > a->n[i]){
				return 1;
			}
		}
	}
	return 2;
}

//多倍長の大小比較 a>b : 1, a<b : -1, エラー時は2
/*
   int KNUTH_numComp(uint16_t a[], uint16_t b[], int size){
   int i;

//a,b共に正のとき
for(i = size; i>= 0; i--){
if(a[i] > b[i]){
return 1;
}
if(b[i] > a[i]){
return -1;
}
}

return 2;
}*/
//int型変数のセット
int setInt(mpv_t *a, uint64_t x, int base){
	int r, i;
	int length = 0;
	clearByZero(a);

	if(x!=0){length = 1;}
	if(x >= 0){
		setSign(a, 1);
	}else{
		setSign(a, -1);
		x = labs(x);
	}

	for(i = 0; i<DIGIT; i++){
		r = x % base;
		x /= base;
		if(x != 0){length++;}
		a->n[i] = r;
	}
	return length;
}

uint64_t convertnumber(mpv_t *a, int base){
	int i;
	uint64_t sum = 0;

	for(i=0; i<DIGIT; i++){
		sum += a->n[i] * pow(base, i);
	}

	return sum;
}
