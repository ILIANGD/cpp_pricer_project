#pragma once
#include "AsianOption.h"

// classe dérivée : AsianCallOption
class AsianCallOption : public AsianOption {
public:
    AsianCallOption(double expiry, double strike, const std::vector<double>& timeSteps);

    // redéfinition de la fonction payoff : h(S) = max(S - K, 0)
    double payoff(double S) const override;
};
;

