#include "AmericanPutOption.h"

AmericanPutOption::AmericanPutOption(double expiry, double strike)
    : AmericanOption(expiry, strike) {}


double AmericanPutOption::payoff(double S) const {
    if (S < _strike) { return (_strike - S);}
    else { return 0.0; }
}
