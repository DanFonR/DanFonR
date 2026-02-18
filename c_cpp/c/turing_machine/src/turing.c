#include <stdio.h>
#include "turing.h"

#define RED "\x1b[41m" /* \x1b == ESC; [...m == color related codes */
#define RESET "\x1b[0m"

void printred(char *str, size_t reader_pos) {
	size_t len;
	for (len = 0; str[len]; len++);

	/* head on blank character */
	if (reader_pos >= len) {
		for (int j = 0; j < reader_pos - len; j++)
			putchar(' ');

		printf("%s%s%c%s\n", str, RED, ' ', RESET);
		return;
	}

	for (int j = 0; str[j]; j++) {
		if (j == reader_pos)
			printf("%s%c%s", RED, str[j], RESET);
		else putchar(str[j]);
	}

	putchar('\n');
}

/*
 * Define functions which que returns next state or -1 on error
 * ex.: q0(str, &i) =>
 * if (str[i] == '1') { * operations * return 2; }; else return -1;
 * function array must be ordered, last function must return array size
*/
bool turing(char str[], StateFunc states[], size_t len) {
	{
		if (!(str) || !(*str)) {
			fprintf(stderr, "empty string\n");
			return false;
		}
		if (states == NULL) {
			fprintf(stderr, "invalid array\n");
			return false;
		}
		if (len == 0) {
			fprintf(stderr, "invalid length\n");
			return false;
		}
	}

	printf("string: %s\n"
		   "accept state: q%zu\n\n", str, len - 1);

	int i = 0, curr_state = 0;

	while (in_range(curr_state, 0, len)) {
		if (i < 0) {
			fprintf(stderr, "head tried to move before start\n");
			return false;
		}

		printf("q%d: ", curr_state);
		printred(str, i);

		curr_state = (*states[curr_state])(str, &i);
	}

	return curr_state == len;
}
