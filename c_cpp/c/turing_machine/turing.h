#ifndef _TURING_H
#define _TURING_H

#include <stdbool.h>

/* gets length of an array */
#define lengthof(arr) (sizeof((arr))/sizeof((arr)[0]))

typedef int (*turing_t[])(char [], int *);

bool turing(char [], int (*states[])(char [], int *), size_t);

int q0(char str[], int *i);
int q1(char str[], int *i);
int q2(char str[], int *i);
int q3(char str[], int *i);
int q4(char str[], int *i);
int q5(char str[], int *i);
int q6(char str[], int *i);
int q7(char str[], int *i);
int q8(char str[], int *i);
int q9(char str[], int *i);
int q10(char str[], int *i);
int q11(char str[], int *i);
int q12(char str[], int *i);
int q13(char str[], int *i);
int q14(char str[], int *i);
int q15(char str[], int *i);
int q16(char str[], int *i);
int q17(char str[], int *i);
int q18(char str[], int *i);
int q19(char str[], int *i);
int q20(char str[], int *i);
int q21(char str[], int *i);
int q22(char str[], int *i);
int q23(char str[], int *i);
int q24(char str[], int *i);
int q25(char str[], int *i);
int q26(char str[], int *i);
int q27(char str[], int *i);
int q28(char str[], int *i);
int q29(char str[], int *i);
int q30(char str[], int *i);
int q31(char str[], int *i);

#endif