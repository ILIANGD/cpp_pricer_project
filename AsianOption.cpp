#include "AsianOption.h"

AsianOption::AsianOption(double expiry, double strikeValue, const std::vector<double>& timestamps)
    : Option(expiry), _strike(strikeValue), _timeSteps(timestamps)
{
    if (_timeSteps.empty()) {
        throw std::invalid_argument("Pour l'Option Asiatique, le timeSteps vector ne peut pas etre vide");
    }
    if (_strike < 0.0) {
        throw std::invalid_argument("AsianOption: strike must be non-negative");
    }
}

const std::vector<double>& AsianOption::getTimeSteps() const {
    return _timeSteps;
}

double AsianOption::getStrike() const {
    return _strike;
}

bool AsianOption::isAsianOption() const {
    return true; // on override pour indiquer que c'est une option asiatique
}

// payoff basé sur la moyenne de la trajectoire
double AsianOption::payoffPath(const std::vector<double>& path) const {
    if (path.empty())
        throw std::invalid_argument("AsianOption::payoffPath: empty path provided");

    // we compute the arithmetic mean of all asset prices in the path.
    double avg = std::accumulate(path.begin(), path.end(), 0.0) / path.size();

    // Asian options pay based on the average price not the final one,
    // so we compute the payoff inherited from CallOption or PutOption
    return payoff(avg);
}

