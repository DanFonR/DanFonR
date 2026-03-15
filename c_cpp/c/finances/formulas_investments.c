#include "finances.h"

inline double eom_present_value(value amount, rate interest_rate, period time) {
    double factor = pow(1 + interest_rate, time);

	return amount * (factor - 1) / (factor * interest_rate);
}

double factor_total(value amount, rate interest_rate,
                    double amount_factor, period time) {

    double factor = (pow(1 + amount_factor, time) - pow(1 + interest_rate, time))
                  / (amount_factor - interest_rate);

    return amount * factor;
}

double cdb(value aplicacao, rate taxa_juros, period periodo_dias) {
    double bruto = future_value(aplicacao, taxa_juros, periodo_dias);
    double imposto = 0.0;

    if (periodo_dias < 30) return 0.0;

    if (periodo_dias <= 180)
        imposto = .225;
    else if (periodo_dias <= 360)
        imposto = .2;
    else if (periodo_dias <= 720)
        imposto = .175;
    else imposto = .15;

    return (bruto - aplicacao) * (1 - imposto) + aplicacao;
}
