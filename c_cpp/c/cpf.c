#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define SECAO 3
#define TAMANHO_CPF 11

typedef enum {
	INVALIDO = -1,
	VALIDO = 1,
	VALIDO_SO_NUMERO = 2
} validade;

typedef enum {
	SEPARADOR_1 = 3,
	SEPARADOR_2 = 7,
	SEPARADOR_3 = 11
} posicoes;


typedef struct {
	unsigned char v2 : 4; /* [0,10] */
	unsigned char v1 : 4;
} digitos_v;

bool checar_cpf(const char * restrict cpf, bool so_digitos) {
	digitos_v digitos = {0, 0};
	char verif_1 = TAMANHO_CPF + (so_digitos? -2 : 1);
	char verif_2 = TAMANHO_CPF + (so_digitos? -1 : 2);
	char digito;

	if (so_digitos) {
		for (char i = 0; i < TAMANHO_CPF - 2; i++) {
			digito = cpf[i] - '0';
			digitos.v1 = (digitos.v1 + digito * (i + 1)) % TAMANHO_CPF;
			digitos.v2 = (digitos.v2 + digito * i) % TAMANHO_CPF;
		}
	}
	else {
		char chave = 0;

		for (char i = 0; i < TAMANHO_CPF; i += 4) {
			#pragma unroll
			for (char j = 0; j < SECAO; j++) {
				chave = (3 * i / 4 + j);
				digito = cpf[i + j] - '0';
				digitos.v1 = (digitos.v1 + digito * (chave + 1)) % TAMANHO_CPF;
				digitos.v2 = (digitos.v2 + digito * chave) % TAMANHO_CPF;
			}
		}
	}

	digitos.v2 = (digitos.v2 + 9 * digitos.v1) % TAMANHO_CPF;

	return (cpf[verif_1] - '0' == digitos.v1)
		&& (cpf[verif_2] - '0' == digitos.v2);
}

validade checar_formato_cpf(const char *cpf) {
	char pos;
	bool so_digitos = true;

	for (pos = 0; cpf[pos] != '\0'; pos++) {
		if (!isdigit(cpf[pos])) {
			so_digitos = false;

			switch (cpf[pos]) {
				case '.':
					if (!(pos == SEPARADOR_1 || pos == SEPARADOR_2))
						return INVALIDO;
					break;
				case '-':
					if (pos != SEPARADOR_3)
						return INVALIDO;
					break;
				default:
					return INVALIDO;
			}
		}

		if (isdigit(cpf[pos]) && !so_digitos
		&& (pos == SEPARADOR_1 || pos == SEPARADOR_2 || pos == SEPARADOR_3))
			return INVALIDO;

		if (pos > 14)
			return INVALIDO;
	}

	if (so_digitos) {
		if (pos == TAMANHO_CPF)
			return VALIDO_SO_NUMERO;

		return INVALIDO;
	}

	if (pos != 14)
		return INVALIDO;

	return VALIDO;
}

int main(int argc, char *argv[]) {
	char cpf[15] = {0};

	switch (argc) {
		case 1:
			fputs(
				"insira seu cpf no formato XXX.XXX.XXX-XX "
				"(ou SAIR p/ sair): ",
				stderr
			);

			if (!scanf("%14s", cpf)) {
				fputs("um erro aconteceu, tente novamente\n", stderr);
				return 1;
			}

			break;

		case 2:
			for (char i = 0; i < 15 && argv[1][i] != '\0'; i++)
				cpf[i] = argv[1][i];
			break;

		default:
			fputs(
				"numero invalido de argumentos\n"
				"este programa checa a validade de um CPF "
				"no formato XXX.XXX.XXX-XX\n",
				stderr
			);
			return 1;
	}

	bool so_digitos = true;

	switch (checar_formato_cpf(cpf)) {
		case INVALIDO:
			fprintf(stderr, "formato invalido de cpf\n");
			return 1;

		case VALIDO: /* fall-through intencional */
			so_digitos = false;

		case VALIDO_SO_NUMERO:
			if (checar_cpf(cpf, so_digitos))
				puts("cpf valido");
			else {
				puts("cpf invalido");
				return 1;
			}
	}

	return 0;
}
