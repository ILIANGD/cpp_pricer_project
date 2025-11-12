#include "EuropeanDigitalCallOption.h"

EuropeanDigitalCallOption::EuropeanDigitalCallOption(double expiry, double strike)
    : EuropeanDigitalOption(expiry, strike) {}

double EuropeanDigitalCallOption::payoff(double S) const {
    return (S >= getStrike()) ? 1.0 : 0.0;
}

EuropeanDigitalOption::optionType EuropeanDigitalCallOption::GetOptionType() const {
    return optionType::digital_call;
}

