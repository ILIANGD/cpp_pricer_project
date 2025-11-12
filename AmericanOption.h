#pragma once
#include "Option.h"
#include <stdexcept>

// représente une option américaine exerçable à tout moment avant l'échéance.
class AmericanOption : public Option {
protected:
    double _strike; // prix d’exercice

public:
    // constructeur
    explicit AmericanOption(double expiry, double strike);

    // identification
    bool isAmericanOption() const override { return true; }

    double getStrike() const { return _strike; }

    virtual double payoff(double S) const = 0;
};