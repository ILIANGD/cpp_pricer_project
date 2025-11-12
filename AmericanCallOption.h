#pragma once
#include "AmericanOption.h"

// option Américaine de type Call 
// Payoff : max(S - K, 0)
class AmericanCallOption : public AmericanOption {
public:
    explicit AmericanCallOption(double expiry, double strike);
    double payoff(double S) const override;
};
