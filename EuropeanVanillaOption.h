#ifndef PROJECT_EUROPEANVANILLAOPTION_H
#define PROJECT_EUROPEANVANILLAOPTION_H
#include "Option.h"


// Déclaration anticipée pour l'ami
class BlackScholesPricer;

/*
  EuropeanVanillaOption : classe ABSTRAITE dérivée de Option.
  - Stocke le strike K (privé)
  - Valide les paramètres (>= 0)
  - Expose un enum pour le type (call/put)
  - Laisse payo(...) et GetOptionType() aux classes dérivées
*/
class EuropeanVanillaOption : public Option {
public:
    // Type d’option (enum de "classe" → portée limitée, pas de collisions)
    enum class optionType { call, put };

    // Doit être redéfini par CallOption / PutOption
    virtual optionType GetOptionType() const = 0;

protected:
    // Constructeur : initialise T (base) et K, et vérifie non-négativité
    explicit EuropeanVanillaOption(double expiry, double strike);

    // Accès K pour les classes dérivées (pas public)
    double getStrike() const {
        return _strike;
    }

private:
    double _strike;  // K
    friend class BlackScholesPricer; // accès direct pour le pricer
};
#endif //PROJECT_EUROPEANVANILLAOPTION_H #pragma once
