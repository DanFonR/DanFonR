#include <stdio.h>
#include "finances.h"

#define TEST_VALS 300000.00, to_percent(4), 5

/* gcc * -lm; ./a.out; rm a.out finances.h.gch */

int main(int argc, char *argv[]) {
	printf("test values: $%.2f, %.2f, %d\n\n", TEST_VALS);
	financing_option options[] = {PRICE, GERMAN, AMERICAN, CAS, IAS, MAS};

	for (int i = 0; i < sizeof(options)/sizeof(options[0]); i++) {
		simulate_financing(TEST_VALS, options[i]);
		puts("");
	}

	return 0;
}
