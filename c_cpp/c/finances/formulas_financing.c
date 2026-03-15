/* https://www.uel.br/projetos/matessencial/basico/financeira/amortiza.html */

#include <stdio.h>
#include <math.h>
#include "finances.h"

double price_system(value amount, rate interest_rate, period time) {
    double factor = pow(1 + interest_rate, time);

    return amount * (factor * interest_rate) / (factor - 1);
}

double german_system(value amount, rate interest_rate, unsigned period) {
	double installment = (amount * interest_rate) / (1 - pow(1 - interest_rate, period));

	return installment;
}

void simulate_financing(value amount, rate interest_rate, period time, financing_option option) {
	{
		char *systems[] = {
			[PRICE] = "PRICE", [GERMAN] = "German", [AMERICAN] = "American",
			[CAS] = "Constanst Amortizations", [IAS] = "Increasing Amortizations",
			[MAS] = "Mixed Amortizations"
		};

		printf("%s System\n\n", systems[option]);
	}

	double installment = 0.0, amortization = 0.0, interest = 0.0, remaining = 0.0;
	double total_installments = 0.0, total_interest = 0.0;
    double initial = amount;
    const char *print_str = "%5d|%11.2lf|%12.2lf|%8.2lf|%9.2lf\n";

    const double price_value = price_system(amount, interest_rate, time);
    const double cas_amortization = amount / time;
    double ias_cas_installment = 0.0, ias_cas_debt = amount;

	switch (option) {
        case PRICE:
		    installment = price_value;
            total_installments = installment * time;
            break;
        case GERMAN:
            installment = german_system(amount, interest_rate, time);
            amortization = installment * pow(1 - interest_rate, time - 1);
            interest = amount * interest_rate;
            total_installments = installment * time + interest;
            break;
        case AMERICAN:
            interest = installment = amount * interest_rate;
            total_installments = amount + interest * time;
            break;
        case CAS:
            amortization = cas_amortization;
            break;
        case IAS:
            installment = amount * (interest_rate + 1.0 / time);
            break;
        case MAS:
            break;
	}

	puts("month|installment|amortization|interest|remaining");

	for (int month = 1; month <= time; month++) {
		switch (option) {
			case PRICE:
				interest = amount * interest_rate;
				amortization = installment - interest;
				break;
			case GERMAN:
                if (month == 1)
                    printf(print_str, 0, interest, 0.0, interest, amount);

	            interest = (amount - amortization) * interest_rate;
				break;
			case AMERICAN:
                if (month == time) {
                    remaining = 0;
                    amortization = amount;
                    installment += amortization;
                }
				break;
			case CAS:
                installment = amortization + amount * interest_rate;
                interest = installment - amortization;
	            total_installments += installment;
				break;
			case IAS:
                interest = amount * interest_rate;
                amortization = installment - interest;
                total_installments += installment;

                if (month % 12 == 0)
	                installment = amount * (interest_rate + 1.0 / (time - month));
				break;
			case MAS:
                ias_cas_installment = cas_amortization + ias_cas_debt * interest_rate;
                installment = (ias_cas_installment + price_value) / 2;
                interest = amount * interest_rate;
                amortization = installment - interest;
                total_installments += installment;
                ias_cas_debt -= cas_amortization;
				break;
		}

        remaining = amount - amortization;

		printf(print_str, month, installment, amortization, interest, remaining);

        switch (option) {
            case AMERICAN:
            case GERMAN:
                amortization /= (1 - interest_rate);
            default:
                amount = remaining;
        }
	}

    total_interest = total_installments - initial;

    printf("\ntotals:\n"
           "installments: %.2lf\n"
           "interest: %.2lf\n",
           total_installments,
           total_interest
    );

    if (option == IAS) {
        printf("credit: %.2lf\n", amount);
    }
}
