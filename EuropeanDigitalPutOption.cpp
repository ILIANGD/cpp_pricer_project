#include "EuropeanDigitalPutOption.h"

EuropeanDigitalPutOption::EuropeanDigitalPutOption(double expiry, double strike)
    : EuropeanDigitalOption(expiry, strike) {}  // base constructor called

double EuropeanDigitalPutOption::payoff(double S) const {
    return (S <= getStrike()) ? 1.0 : 0.0;
}

EuropeanDigitalOption::optionType EuropeanDigitalPutOption::GetOptionType() const {
    return optionType::digital_put;
}

