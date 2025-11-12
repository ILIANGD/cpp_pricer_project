#include "BlackScholesPricer.h"
#include <iostream>
#include <cmath>
#include <stdexcept>

//cdf normal
double BlackScholesPricer::norm_cdf(double x) {
    return 0.5 * std::erfc(-x / std::sqrt(2.0));
}

// constructeur statique vanilla
BlackScholesPricer BlackScholesPricer::ForVanilla(
    EuropeanVanillaOption* option,
    double asset_price,
    double interest_rate,
    double volatility)
{
    if (!option)
        throw std::invalid_argument("Vanilla option pointer is null");
    if (asset_price <= 0.0)
        throw std::invalid_argument("Asset price must be > 0");
    if (volatility <= 0.0)
        throw std::invalid_argument("Volatility must be > 0");

    BlackScholesPricer p;
    p._opt = option;
    p._digitalOpt = nullptr;
    p._S = asset_price;
    p._r = interest_rate;
    p._v = volatility;
    return p;
}


// constructeur statique digital
BlackScholesPricer BlackScholesPricer::ForDigital(
    EuropeanDigitalOption* option,
    double asset_price,
    double interest_rate,
    double volatility)
{
    if (!option)
        throw std::invalid_argument("Digital option pointer is null");
    if (asset_price <= 0.0)
        throw std::invalid_argument("Asset price must be > 0");
    if (volatility <= 0.0)
        throw std::invalid_argument("Volatility must be > 0");

    BlackScholesPricer p;
    p._opt = nullptr;
    p._digitalOpt = option;
    p._S = asset_price;
    p._r = interest_rate;
    p._v = volatility;
    return p;
}

// prix vanilla
double BlackScholesPricer::priceVanilla() const {
    if (!_opt){
        throw std::runtime_error("No vanilla option assigned to pricer");
    }
    const double T = _opt->getExpiry();
    const double K = _opt->_strike;
    const auto type = _opt->GetOptionType();

    if (T <= 0.0){ return _opt->payoff(_S);
    }

    const double sqrtT = std::sqrt(T);
    const double volSqrtT = _v * sqrtT;
    const double d1 = (std::log(_S / K) + (_r + 0.5 * _v * _v) * T) / volSqrtT;
    const double d2 = d1 - volSqrtT;

    if (type == EuropeanVanillaOption::optionType::call) {
        // C = S Φ(d1) - K e^{-rT} Φ(d2)
        return _S * norm_cdf(d1) - K * std::exp(-_r * T) * norm_cdf(d2);
    }
    else {
        // P = K e^{-rT} Φ(-d2) - S Φ(-d1)
        return K * std::exp(-_r * T) * norm_cdf(-d2) - _S * norm_cdf(-d1);
    }
        
}

// prix digital
double BlackScholesPricer::priceDigital() const {
    if (!_digitalOpt) {
        throw std::runtime_error("No digital option assigned to pricer");
    }
        

    const double T = _digitalOpt->getExpiry();
    const double K = _digitalOpt->_strike;
    const auto type = _digitalOpt->GetOptionType();

    if (T <= 0.0) return _digitalOpt->payoff(_S);

    const double sqrtT = std::sqrt(T);
    const double volSqrtT = _v * sqrtT;
    const double d1 = (std::log(_S / K) + (_r + 0.5 * _v * _v) * T) / volSqrtT;
    const double d2 = d1 - volSqrtT;

    if (type == EuropeanDigitalOption::optionType::digital_call) {
        // Digital call: e^{-rT} Φ(d2)
        return std::exp(-_r * T) * norm_cdf(d2);
    }
        
    else {
        // Digital call: e^{-rT} Φ(d2)
        return std::exp(-_r * T) * norm_cdf(-d2);
    }
}

// delta vanilla
double BlackScholesPricer::delta() const {
    if (!_opt)
        throw std::runtime_error("Delta is only defined for vanilla options");

    const double T = _opt->getExpiry();
    const double K = _opt->_strike;
    const auto type = _opt->GetOptionType();

    if (T <= 0.0) {
        if (type == EuropeanVanillaOption::optionType::call)
            return (_S > K) ? 1.0 : 0.0;
        else
            return (_S < K) ? -1.0 : 0.0;
    }

    const double sqrtT = std::sqrt(T);
    const double d1 = (std::log(_S / K) + (_r + 0.5 * _v * _v) * T) / (_v * sqrtT);

    if (type == EuropeanVanillaOption::optionType::call)
        return norm_cdf(d1);
    else
        return norm_cdf(d1) - 1.0;
}
