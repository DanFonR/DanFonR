#include <stdio.h>
#include <stdint.h>

#define ALL_26_LETTERS ( (uint32_t)((1 << 26) - 1) )
#define STR_SIZE 100
#define DEBUG

uint8_t is_pangram(const char *str) {
	uint32_t letters = 0U;

	while (*str) {
		if ('a' <= *str && *str <= 'z')
			letters |= 1U << (*str - 'a');
		else if ('A' <= *str && *str <= 'Z')
			letters |= 1U << (*str - 'A');

		str++;
	}

	return letters == ALL_26_LETTERS;
}

int main() {
	#ifdef DEBUG
	const char str[] = "Furtadas cinco zebras, jegues vermelhos,"
						 		   " whisky e xales. Por quê?";
	/*
	* others:
	* "Pack my box with five dozen liquor jugs";
	* "The quick brown fox jumps over the lazy dog";
	* "Mr. Jock, TV quiz PhD, bags few lynx"
	*/
	#else
	char str[STR_SIZE];

	printf("type a string to check if it's a pangram: ");
	if (!scanf("%99[^\n]", str)) return 1;
	#endif

	printf("\"%s\" is%s a pangram\n", str, is_pangram(str)? "" : "n't");
	return 0;
}
