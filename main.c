#include "main.h"
#include "add.h"
#include "sub.h"
#include "multiple.h"
#include "division.h"

int main(void){
	uint32_t i, j;
	uint64_t checknumber, correctnumber;
	mpv8_t aa, bb, qq, rr;
	int LengthOfa = 0;
	int LengthOfb= 0;
	int din = 0;
	int dout = 0;
	int base = G_MAIN_BASE_8;

	clearByZero8_t(&aa);
	clearByZero8_t(&bb);
	clearByZero8_t(&qq);
	clearByZero8_t(&rr);

	LengthOfa = setInt8_t(&aa, 5, base);
	LengthOfb = setInt8_t(&bb, 2, base);
	KNUTH_div8_t(&aa, &bb, &qq, &rr, LengthOfa, LengthOfb, base);
	Displaympv8_t(&qq);
	Displaympv8_t(&rr);

	return 0;
}

int clearByZero(mpv_t *a){
	int i;

	a->sign = true;
	for(i=0; i<G_MAIN_DIGIT; i++){
		a->n[i] = 0;
	}

	return 0;
}

int clearByZero8_t(mpv8_t *a){
	int i;

	a->sign = true;
	for(i=0; i<G_MAIN_DIGIT; i++){
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
	for(i=G_MAIN_DIGIT-1; i>=0; i--){
		printf(" %x ", a->n[i]);
	}
	putchar('\n');

	return 0;
}

int Displaympv8_t(const mpv8_t *a){
	int i;

	if(a->sign == true){
		printf(" + ");
	}else{
		printf(" - ");
	}
	for(i=G_MAIN_DIGIT-1; i>=0; i--){
		printf(" %x ", a->n[i]);
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

int getSign8_t(mpv8_t *p){
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

void setSign8_t(mpv8_t *p, int s){
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
void getAbs8_t(mpv8_t *a, mpv8_t *b){
	copympv8_t(a, b);
	setSign8_t(b, 1);
}

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
	for(i = 0; i < G_MAIN_DIGIT; i++){
		b->n[i] = a->n[i];
	}
}

void copympv8_t(mpv8_t *a, mpv8_t *b){
	int i;

	clearByZero8_t(b);
	b->sign = a->sign;
	for(i = 0; i < G_MAIN_DIGIT; i++){
		b->n[i] = a->n[i];
	}
}

//多倍長の大小比較 a>b : 1, a<b : -1, エラー時は2
int numComp8_t(mpv8_t *a, mpv8_t *b){
	int i;
	int getSigna = getSign8_t(a);
	int getSignb = getSign8_t(b);

	if(getSigna > getSignb ){
		return 1;
	}
	if(getSigna < getSignb ){
		return -1;
	}
	//a,b共に正のとき
	if(getSigna == 1 || getSignb == 1){
		for(i = G_MAIN_DIGIT-1; i>= 0; i--){
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
		for(i = G_MAIN_DIGIT-1; i>= 0; i--){
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
		for(i = G_MAIN_DIGIT-1; i>= 0; i--){
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
		for(i = G_MAIN_DIGIT-1; i>= 0; i--){
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

//int型変数のセット
int setInt(mpv_t *a, int x, int base){
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

	for(i = 0; i<G_MAIN_DIGIT; i++){
		r = x % base;
		x /= base;
		if(x != 0){length++;}
		a->n[i] = r;
	}
	return length;
}

int setInt8_t(mpv8_t *a, int x, int base){
	int r, i;
	int length = 0;
	clearByZero8_t(a);

	if(x!=0){length = 1;}
	if(x >= 0){
		setSign8_t(a, 1);
	}else{
		setSign8_t(a, -1);
		x = labs(x);
	}

	for(i = 0; i<G_MAIN_DIGIT; i++){
		r = x % base;
		x /= base;
		if(x != 0){length++;}
		a->n[i] = r;
	}
	return length;
}

uint64_t convertnumber8_t(mpv8_t *a, int base){
	int i;
	uint64_t sum = 0;

	for(i=0; i<G_MAIN_DIGIT; i++){
		sum += a->n[i] * pow((double)base, (double)i);
	}

	return sum;
}

uint64_t convertnumber(mpv_t *a, int base){
	int i;
	uint64_t sum = 0;

	for(i=0; i<G_MAIN_DIGIT; i++){
		sum += a->n[i] * pow((double)base, (double)i);
	}

	return sum;
}
