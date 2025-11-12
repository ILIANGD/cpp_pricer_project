#include "AmericanOption.h"


AmericanOption::AmericanOption(double expiry, double strike)
    : Option(expiry), _strike(strike)
{
    if (_strike < 0.0) {
        throw std::invalid_argument("AmericanOption: strike must be non-negative");
    }
}
