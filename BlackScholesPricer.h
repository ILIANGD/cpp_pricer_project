#pragma once
#include "EuropeanVanillaOption.h"
#include "EuropeanDigitalOption.h"
#include <cmath>
#include <stdexcept>

class BlackScholesPricer {
private:
    // membres prives
    BlackScholesPricer() = default; // constructeur privé
    EuropeanVanillaOption* _opt = nullptr;
    EuropeanDigitalOption* _digitalOpt = nullptr;
    double _S = 0.0;  // prix de l’actif
    double _r = 0.0;  // taux d’intérêt
    double _v = 0.0;  // volatilité


public:

    BlackScholesPricer(EuropeanVanillaOption* option,
        double asset_price,
        double interest_rate,
        double volatility)
        : _opt(option), _digitalOpt(nullptr),
        _S(asset_price), _r(interest_rate), _v(volatility)
    {
        if (!option) throw std::invalid_argument("Vanilla option pointer is null");
        if (asset_price <= 0.0) throw std::invalid_argument("Asset price must be > 0");
        if (volatility <= 0.0) throw std::invalid_argument("Volatility must be > 0");
    }

    // Digital option constructor
    BlackScholesPricer(EuropeanDigitalOption* option,
        double asset_price,
        double interest_rate,
        double volatility)
        : _opt(nullptr), _digitalOpt(option),
        _S(asset_price), _r(interest_rate), _v(volatility)
    {
        if (!option) throw std::invalid_argument("Digital option pointer is null");
        if (asset_price <= 0.0) throw std::invalid_argument("Asset price must be > 0");
        if (volatility <= 0.0) throw std::invalid_argument("Volatility must be > 0");
    }




    // factory methods
    static BlackScholesPricer ForVanilla(EuropeanVanillaOption* option,
        double asset_price,
        double interest_rate,
        double volatility);

    static BlackScholesPricer ForDigital(EuropeanDigitalOption* option,
        double asset_price,
        double interest_rate,
        double volatility);

    // methods
    double priceVanilla() const;
    double priceDigital() const;
    double delta() const;
    static double norm_cdf(double x);

    double operator()() const {
        if (_opt) return priceVanilla();
        if (_digitalOpt) return priceDigital();
        throw std::runtime_error("No option assigned to pricer");
    }



};
