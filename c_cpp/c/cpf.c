#include <stdio.h>

int checar_cpf(char cpf[15]) {
	int digito_v1 = 0, digito_v2 = 0, ignorado = 0;

	for (int i = 0; i < 11; i++) {
		if (cpf[i] == '.') {
			ignorado++;
			continue;
		}

		digito_v1 += (cpf[i] - '0') * (i + 1 - ignorado);
		digito_v2 += (cpf[i] - '0') * (i - ignorado);
	}

	digito_v2 = (digito_v2 + 9 * digito_v1) % 11;
	digito_v1 %= 11;

	return (cpf[12] - '0' == digito_v1)
							&& (cpf[13] - '0' == digito_v2);
}

int checar_formato_cpf(char cpf[15]) {
	int i;

	for (i = 0; cpf[i] != '\0'; i++) {
		if ((cpf[i] == '.' && !(i == 3 || i == 7)) /* . fora do lugar */
			|| (cpf[i] == '-' && i != 11) /* - fora do lugar */
			|| (!(('0' <= cpf[i] && cpf[i] <= '9') /* nao eh cpf */
					|| cpf[i] == '.' || cpf[i] == '-'))
			|| (('0' <= cpf[i] && cpf[i] <= '9') /* digito fora do lugar */
					&& !(i != 3 || i != 7 || i != 11))
				) return 0;
	}

	if (i != 14) return 0;

	return 1;
}

int main(int argc, char *argv[]) {
	char cpf[15];

	switch (argc) {
		case 1:
			fprintf(stderr, "insira seu cpf no formato XXX.XXX.XXX-XX: ");

			if (!scanf("%14s", cpf)) {
				fprintf(stderr, "um erro aconteceu, tente novamente\n");
				return -1;
			}

			break;

		case 2:
			for (int i = 0; (cpf[i] = argv[1][i]) != '\0'; i++);
			break;

		default:
			fprintf(stderr, "numero invalido de argumentos\n"
			"este programa checa a validade de um cpf no formato XXX.XXX.XXX-XX\n");
			return -1;
	}

	if (checar_formato_cpf(cpf) == 0) {
		fprintf(stderr, "formato invalido de cpf\n"
		"inclua pontos e tracos\n");
		return -1;
	}
	else if (checar_cpf(cpf) == 0) {
		puts("cpf invalido");
		return 0;
	}
	
	puts("cpf valido");
	
	return 0;
}
