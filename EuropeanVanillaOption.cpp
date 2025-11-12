//
// Created by Ilian Segoin on 23/10/2025.
//

#include "EuropeanVanillaOption.h"
#include <stdexcept>  // <-- nécessaire pour std::invalid_argument

/*
  Implémentation minimale :
  - Appelle le constructeur de base Option(expiry)
  - Vérifie expiry >= 0 et strike >= 0
*/
EuropeanVanillaOption::EuropeanVanillaOption(double expiry, double strike)
    : Option(expiry), _strike(strike)
{
    if (expiry < 0.0 || strike < 0.0) { // fait en sorte que les valeurs soit pas negative
        throw std::invalid_argument("expiry and strike must be nonnegative");
    }
}