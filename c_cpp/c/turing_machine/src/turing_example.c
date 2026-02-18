#include <stdio.h>
#include "turing.h"

int q0(char str[], int *i) {
	switch (str[*i]) {
		case 'X':
			(*i)++;
			return 1;
		default:
			return -1;
	}
}

int q1(char str[], int *i) {
	switch (str[*i]) {
		case '1':
			(*i)++;
			return 1;
		case '+':
			str[*i] = '1';
			(*i)++;
			return 2;
		default:
			return -1;
	}
}

int q2(char str[], int *i) {
	switch (str[*i]) {
		case '1':
			(*i)++;
			return 2;
		case '\0':
			(*i)--;
			return 3;
		default:
			return -1;
	}
}

int q3(char str[], int *i) {
	switch (str[*i]) {
		case '1':
			str[*i] = '\0';
			(*i)--;
			return 4;
		default:
			return -1;
	}
}

int q4(char str[], int *i) {
	return 5;
}

int q5(char str[], int *i) {
	switch (str[*i]) {
		case 'B':
		case 'C':
			(*i)++;
			return 5;
		case '\0':
			(*i)--;
			return 6;
		default:
			return -1;
	}
}

int q6(char str[], int *i) {
	return 7;
}

int main() {
	char test[] = "X111+1111";
	StateFunc states[] = {q0, q1, q2, q3, q4};
	size_t states_len = lengthof(states);
	puts((turing(test, states, states_len))? "\naceita\n" : "\nrejeita\n");
	printf("apos operacao: %s\n", test);
	return 0;
}
