#pragma once 
#include "Option.h"
#include "Monte Carlo.h"       // Singleton random number generator
#include <vector>
#include <stdexcept>

class BlackScholesMCPricer {
private:
    Option* _option;
    double _S0;
    double _r;
    double _sigma;

    int _nbPaths = 0;     // total number of simulated paths
    double _mean = 0.0;   // running mean of payoffs
    double _M2 = 0.0;     // running sum of squares of differences (for variance)

public:
    // the constructor
    BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility);

    int getNbPaths() const;  // getter for number of paths

    void generate(int nb_paths);   // Monte Carlo simulation 

    // return current price estimate
    double operator()() const;

    // intervalle de confiance (95%) 
    std::vector<double> confidenceInterval() const;
};
