#include "clear.h"

int clearByZero8_t(mpv8_t *a){
	int i;

	a->sign = true;
	for(i=0; i<G_MAIN_DIGIT; i++){
		a->n[i] = 0;
	}

	return 0;
}