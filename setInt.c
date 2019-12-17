#include "setInt.h"
#include "clear.h"
#include "sign.h"

//int型変数のセット
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