#include "AsianCallOption.h"

//constructeur
AsianCallOption::AsianCallOption(double expiry, double strike, const std::vector<double>& timeSteps)
    : AsianOption(expiry, strike, timeSteps) {}

// fonction payoff 
double AsianCallOption::payoff(double S) const {
    if (S > _strike) {
        return S - _strike;   // payoff positif si S > K
    }
    else {
        return 0.0;           // sinon, l’option ne paie rien
    }
}
