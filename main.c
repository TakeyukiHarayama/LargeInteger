#include "main.h"
#include "division.h"
#include "clear.h"
#include "setInt.h"
#include "disp.h"

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
	//aa / bb = bb * qq + rr
	KNUTH_div8_t(&aa, &bb, &qq, &rr, LengthOfa, LengthOfb, base);
	Displaympv8_t(&qq);
	Displaympv8_t(&rr);

	return 0;
}
