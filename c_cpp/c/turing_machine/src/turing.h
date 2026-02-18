#ifndef _TURING_H
#define _TURING_H

#include <stdbool.h>

/* gets length of an array */
#define lengthof(arr) (sizeof((arr))/sizeof((arr)[0]))

/* check if var in [lower,upper) */
#define in_range(var, lower, upper) ((lower) <= (var) && (var) < (upper))

typedef int (*StateFunc)(char [], int *);

bool turing(char [], StateFunc states[], size_t);

#endif
