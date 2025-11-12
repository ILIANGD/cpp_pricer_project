#include "AsianPutOption.h"

AsianPutOption::AsianPutOption(double expiry, double strike, const std::vector<double>& timeSteps)
    : AsianOption(expiry, strike, timeSteps) {}

double AsianPutOption::payoff(double S) const {
    if (S < _strike) {
        return _strike - S;   // payoff positif si S < K
    }
    else {
        return 0.0;           // sinon, pas de payoff
    }
}