/* code adapted from a video by MrGee Math */
/* https://youtu.be/G2AjIRBzmeQ?t=7m11s */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MILLION 1000 * 1000
#define TEN_M 10 * MILLION
#define HUN_M 100 * MILLION
#define BILLION 1000 * 1000 * 1000

typedef struct {
	unsigned char car : 2;
	unsigned char player : 2;
	unsigned char host : 2;
} monty_t;

void run_sim(size_t iters) {
	clock_t t0 = clock(), t1;
	size_t swaps = 0, no_swaps;
	monty_t sim;

	for (size_t i = 0; i < iters; i++) {
		sim.car = rand() % 3;
		sim.player = rand() % 3;

		sim.host = (sim.car == sim.player)? (sim.player + 1) % 3 : 3 - sim.player - sim.car;
		sim.player = 3 - sim.player - sim.host;
		
		swaps += (size_t)(sim.player == sim.car);
	}

	no_swaps = iters - swaps;

	double swap_ratio = ((double)swaps / (double)iters);
	double no_swap_ratio = ((double)no_swaps / (double)iters);
	t1 = clock();

	printf(
		"out of %zu runs,\n"
		"swapping won %zu (%.2f%%)\n"
		"not swapping won %zu (%.2f%%)\n",
		iters, swaps, swap_ratio * 100,
		no_swaps, no_swap_ratio * 100
	);

	if (t1 == -1 || t0 == -1) return;

	double total_time = (double)(t1 - t0) / CLOCKS_PER_SEC;

	printf("elapsed time: %.3fs\n", total_time);
}

int main(int argc, char **argv) {
	size_t iters;
	srand(time(NULL));
	if (argc != 2) iters = HUN_M;
	else sscanf(argv[1], "%zu", &iters);

	run_sim(iters);
	return 0;
}
