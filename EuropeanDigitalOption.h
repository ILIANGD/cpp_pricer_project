#pragma once
#include "Option.h"

class BlackScholesPricer;

// Base class for digital options
class EuropeanDigitalOption : public Option {
public:
    enum class optionType { digital_call, digital_put };

    virtual optionType GetOptionType() const = 0;

protected:
    explicit EuropeanDigitalOption(double expiry, double strike);

    double getStrike() const { return _strike; }

private:
    double _strike;
    friend class BlackScholesPricer;
};
