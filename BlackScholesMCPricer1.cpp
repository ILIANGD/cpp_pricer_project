#include "BlackScholesMCPricer1.h"
#include <cmath>
#include "AsianOption.h"
#include "Monte Carlo.h"

// the constructor
BlackScholesMCPricer::BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility)
    : _option(option), _S0(initial_price), _r(interest_rate), _sigma(volatility)
{
    if (!_option) throw std::invalid_argument("Null option pointer.");
    if (_S0 <= 0) throw std::invalid_argument("Initial price must be positive.");
    if (_sigma <= 0) throw std::invalid_argument("Volatility must be positive.");
}

int BlackScholesMCPricer::getNbPaths() const { return _nbPaths; }

void BlackScholesMCPricer::generate(int nb_paths) {    //  Monte Carlo simulation 
    if (nb_paths <= 0) throw std::invalid_argument("Number of paths must be positive.");

    double T = _option->getExpiry();
    double discount = std::exp(-_r * T);


    for (int i = 0; i < nb_paths; ++i) {
        double discountedPayoff = 0.0;
        if (_option->isAsianOption()) {
            const AsianOption* asian = dynamic_cast<const AsianOption*>(_option);
            std::vector<double> path;
            for (double t : asian->getTimeSteps()) {
                double Z = MT::rand_norm(); // loi normal N(0,1)
                double ST = _S0 * std::exp((_r - 0.5 * _sigma * _sigma) * T + _sigma * std::sqrt(T) * Z);
            }
            discountedPayoff = discount * _option->payoffPath(path);
        }
        else {
            double Z = MT::rand_norm();
            double ST = _S0 * std::exp((_r - 0.5 * _sigma * _sigma) * T + _sigma * std::sqrt(T) * Z);
            discountedPayoff = discount * _option->payoff(ST);
        }

        // update mean and variance online (Welford’s algorithm), numerically stable way to compute running mean and variance without storing them in your memory
        _nbPaths++;
        double delta = discountedPayoff - _mean; // compute the deviation from the current mean 
        _mean += delta / _nbPaths;               // update the mean 
        _M2 += delta * (discountedPayoff - _mean); // update an auxiliary term M2
    }
}

// return current price estimate
double BlackScholesMCPricer::operator()() const {
    if (_nbPaths == 0)
        throw std::runtime_error("Monte Carlo estimate undefined: no paths generated.");
    return _mean;
}

// intervalle de confiance (95%) 
std::vector<double> BlackScholesMCPricer::confidenceInterval() const {
    if (_nbPaths < 2)
        throw std::runtime_error("Not enough samples for confidence interval.");

    double variance = _M2 / (_nbPaths - 1);
    double stdError = std::sqrt(variance / _nbPaths);
    double z = 1.96; // 95% confidence

    return { _mean - z * stdError, _mean + z * stdError };
}