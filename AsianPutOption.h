#pragma once
#include "AsianOption.h"


class AsianPutOption : public AsianOption {
public:

    AsianPutOption(double expiry, double strike, const std::vector<double>& timeSteps);

    // pareil redéfinition de la fonction payoff : h(S) = max(K - S, 0)
    double payoff(double S) const override;
};

