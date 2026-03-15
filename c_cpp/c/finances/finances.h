/* eom == end of month; som == start of month */

#ifndef FINANCES_H
#define FINANCES_H

#include <math.h>

#define to_monthly(rate) pow((1 + (rate)), 1.0/12) - 1
#define to_percent(rate) ((double)(rate) / 100)

#define future_value(value, rate, period) \
    (value) * pow(1 + (rate), (period)) /* also for eom total */

#define eom_to_som(eom_val, rate) (eom_val) * (1 + (rate))

#define deferred_value(value, rate, deferment_period) \
    (value) / pow(1 + (rate), (deferment_period))

typedef unsigned int period;
typedef double rate;
typedef double value;

typedef enum {
    PRICE,
    GERMAN,
    AMERICAN,
    CAS, /* constant amortizations */
    IAS, /* increasing amortizations */
    MAS, /* mixed amortizations */
} financing_option;

/* financing options */

double price_system(value, rate, period);

double german_system(value, rate, period);

void show_increasing_amortizations(value, rate, period);

void show_mixed_amortizations(value, rate, period);

void show_german_table(value, rate, period);

void show_american_table(value, rate, period);

void simulate_financing(value, rate, period, financing_option);


/* investment options */

inline double eom_present_value(value, rate, period);

double factor_total(value, rate, double factor, period);

double cdb(value, rate, period);


#endif
