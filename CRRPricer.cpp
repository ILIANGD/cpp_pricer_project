#include "CRRPricer.h"


CRRPricer::CRRPricer(Option* option, int depth, double asset_price,
    double up, double down, double interest_rate)
{
    _option = option;
    _depth = depth;
    _up = up;
    _down = down;
    S0 = asset_price;
    _interest_rate = interest_rate;

    // we reject Asian options
    if (_option && _option->isAsianOption()) { // -> is a pointer to an object
        throw std::invalid_argument("CRRPricer: Asian options cannot be priced with the CRR model.");
    }

    if (!_option) { //vérification du pointeur
        throw std::invalid_argument("Le pointeur vers l'option est nul (null pointer)");
    }

    if (S0 <= 0.0) { // on verifie les parametres
        throw std::invalid_argument("Initial asset price must be positive.");
    }
    if (_up <= _down) {
        throw std::invalid_argument("Up factor must be greater than down factor.");
    }
    if (_down <= -1.0 || _interest_rate <= -1.0) {
        throw std::invalid_argument("Down factor and interest rate must be > -1.");
    }
    if (_depth <= 0) {
        throw std::invalid_argument("Tree depth must be positive.");
    }

    if (!(_down < _interest_rate && _interest_rate < _up)) {
        // on verifie la condition d’absence d’arbitrage : D < R < U
        throw std::invalid_argument("Arbitrage détecté : il faut avoir D < R < U.");
    }

    // on calcule la probabilité neutre au risque
    _q = (_interest_rate - _down) / (_up - _down);

    _assetTree.setDepth(_depth);
    _valueTree.setDepth(_depth);

    // on cree l'arbre pour le prix de l'actif
    for (int n = 0; n <= _depth; n++) {
        for (int i = 0; i <= n; i++) {
            double S = S0 * pow(1 + up, i) * pow(1 + down, n - i); // on calcule a partir de la formule de l'enonce
            _assetTree.setNode(n, i, S); // on utilise le setter pour integrer la valeur
        }
    }
}

// Constructeur Black-Scholes approximation
CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double r, double sigma)
    : _option(option), _depth(depth), S0(asset_price)
{
    if (!_option) {
        throw std::invalid_argument("Null option pointer.");
    }

    if (_depth <= 0) {
        throw std::invalid_argument("Depth must be positive.");
    }

    if (S0 <= 0.0) {
        throw std::invalid_argument("Asset price must be positive.");
    }

    if (sigma <= 0.0) {
        throw std::invalid_argument("Volatility must be positive.");
    }

    // on divise la période en N intervalles
    double T = _option->getExpiry();
    double h = T / _depth;

    // formules du modèle binomial comme approximation de Black–Scholes
    _up = std::exp((r + 0.5 * sigma * sigma) * h + sigma * std::sqrt(h)) - 1.0;
    _down = std::exp((r + 0.5 * sigma * sigma) * h - sigma * std::sqrt(h)) - 1.0;
    _interest_rate = std::exp(r * h) - 1.0;

    if (!(_down < _interest_rate && _interest_rate < _up)) {
        throw std::invalid_argument("Arbitrage detected in Black-Scholes parameters.");
    }

    _q = (_interest_rate - _down) / (_up - _down);

    _assetTree.setDepth(_depth);
    _valueTree.setDepth(_depth);
    _exerciseTree.setDepth(_depth);

    for (int n = 0; n <= _depth; ++n) {
        for (int i = 0; i <= n; ++i) {
            double S = S0 * pow(1 + _up, i) * pow(1 + _down, n - i);
            _assetTree.setNode(n, i, S);
        }
    }
}


// Procedure CRR
void CRRPricer::compute() {
    for (int i = 0; i <= _depth; ++i) {
        double S = _assetTree.getNode(_depth, i); // on recupere le prix du sous_jacent au dernier niveau
        double h = _option->payoff(S);            // on calcule le payout de l’option à l’échéance pour ce prix.
        _valueTree.setNode(_depth, i, h);         // on stock ce payoff dans l'arbre de valeur de l'option
        _exerciseTree.setNode(_depth, i, false); // à l’échéance, pas de décision anticipée
    }

    // on implemente backward induction
    for (int n = _depth - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            double continuation =
                (_q * _valueTree.getNode(n + 1, i + 1) +   // cas "hausse"
                    (1 - _q) * _valueTree.getNode(n + 1, i))  // cas "baisse"
                / (1 + _interest_rate);                    // actualisation



            double S = _assetTree.getNode(n, i);
            double intrinsic = _option->payoff(S);
            // cas américain : on choisit le max
            double nodeValue = continuation;
            bool exercise = false;

            if (_option->isAmericanOption()) {
                if (intrinsic >= continuation) {
                    nodeValue = intrinsic;
                    exercise = true;
                }
            }

            _valueTree.setNode(n, i, nodeValue);       // on stocke la valeur du nœud
            _exerciseTree.setNode(n, i, exercise);

        }
    }
    _computed = true;
}

// getter pour H(n, i) 
double CRRPricer::getH(int i, int n) {
    return _valueTree.getNode(n, i);
}

// Operator() qui permet d'avoir le prix de l'option
double CRRPricer::operator()(bool closed_form) {
    if (closed_form) { // closed form is true when pricing European option
        // closed-form binomial expression
        double price = 0.0;
        for (int i = 0; i <= _depth; ++i) {
            double S = _assetTree.getNode(_depth, i);   // S(N, i)
            double payoff = _option->payoff(S);         // h(S(N, i))

            // coefficient binomial C(N, i) = N! / (i! * (N - i)!)
            double comb = std::tgamma(_depth + 1) /
                (std::tgamma(i + 1) * std::tgamma(_depth - i + 1)); // tgamma permet d'avoir le factoriel

            // on ajoute les autres termes de la formule
            price += comb * pow(_q, i) * pow(1 - _q, _depth - i) * payoff;
        }

        // Discount back to present
        price /= pow(1 + _interest_rate, _depth);
        return price;
    }

    // sinon on utilise le backward induction (CRR tree)
    if (!_computed) {
        compute();
    }
    return _valueTree.getNode(0, 0);


}


bool CRRPricer::getExercise(int n, int i) const { // Returns true if the option should be exercised early at that node.
    return _exerciseTree.getNode(n, i); //Returns false if it’s better to continue holding.
}

// ===== Affichage =====
void CRRPricer::displayTrees() const {
    std::cout << "Asset Price Tree:\n";
    _assetTree.display();

    std::cout << "Option Value Tree:\n";
    _valueTree.display();

    if (_option->isAmericanOption()) {
        std::cout << "Early Exercise Tree (1 = exercise):\n";
        for (int n = 0; n <= _depth; ++n) {
            for (int i = 0; i <= n; ++i) {
                std::cout << (_exerciseTree.getNode(n, i) ? "1 " : "0 ");
            }
            std::cout << "\n";
        }
    }
}