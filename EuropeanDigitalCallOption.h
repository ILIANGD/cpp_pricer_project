#ifndef PROJECT_EUROPEANDIGITALCALLOPTION_H
#define PROJECT_EUROPEANDIGITALCALLOPTION_H

#include "EuropeanDigitalOption.h"

class EuropeanDigitalCallOption : public EuropeanDigitalOption {
public:
    explicit EuropeanDigitalCallOption(double expiry, double strike);

    double payoff(double S) const override;
    optionType GetOptionType() const override;
};

#endif // PROJECT_EUROPEANDIGITALCALLOPTION_H

