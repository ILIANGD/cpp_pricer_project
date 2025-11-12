#include "AmericanCallOption.h"

AmericanCallOption::AmericanCallOption(double expiry, double strike)
    : AmericanOption(expiry, strike) {}

double AmericanCallOption::payoff(double S) const {
    if (S > _strike) { return  (S - _strike); }
    else { return 0.0; }
}