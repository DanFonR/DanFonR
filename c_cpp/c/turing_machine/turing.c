#include <stdio.h>
#include "turing.h"

#define RED "\x1b[41m" /* \x1b == ESC; [...m == color related codes */
#define RESET "\x1b[0m"

void printred(char *str, size_t i) {
	size_t len;
	for (len = 0; str[len]; len++);

	if (i >= len) {
		for (int j = 0; j < i - len; j++)
			putchar(' ');

		printf("%s%s%c%s\n", str, RED, ' ', RESET);
		return;
	}

	for (int j = 0; str[j]; j++) {
		if (j == i)
			printf("%s%c%s", RED, str[j], RESET);
		else putchar(str[j]);
	}

	putchar('\n');
}

/*
 * Defina funções tal que o retorno seja o próximo estado ou -1 em erro
 * ex.: q0(str, &i) =>
 * if (str[i] == '1') {*operacoes* return 2}; else return -1;
 * array de funcoes deve estar em ordem crescente
 * ultima funcao deve retornar tamanho do array
*/
bool turing(char str[], int (*states[])(char [], int *), size_t len) {
	{
		if (str[0] == '\0' || str == NULL) {
			fprintf(stderr, "string vazia\n");
			return false;
		}
		if (states == NULL) {
			fprintf(stderr, "array invalido\n");
			return false;
		}
		if (len == 0) {
			fprintf(stderr, "comprimento invalido\n");
			return false;
		}
	}

	printf("string: %s\naceitacao: q%zu\n\n", str, len - 1);
	int i = 0, curr_state = 0;

	while (curr_state != -1 && curr_state != len) {
		printf("q%d: ", curr_state);
		printred(str, i);
		curr_state = (*states[curr_state])(str, &i);
	}

	return curr_state == len;
}
