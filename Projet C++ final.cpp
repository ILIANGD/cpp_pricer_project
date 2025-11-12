// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "BinaryTree2.h"
//#include <iostream>
//#include "Option.h"
//#include "EuropeanVanillaOption.h"
//#include "CallOption.h"
//#include "PutOption.h"
//#include "BlackScholesPricer.h"
//#include "CRRPricer.h"
//#include "EuropeanDigitalCallOption.h"
//#include "EuropeanDigitalPutOption1.h"
//#include "AsianCallOption.h"
//#include "AsianPutOption.h"
//#include "BlackScholesMCPricer1.h"
//#include "AmericanPutOption.h"
//#include "AmericanCallOption.h"
//#include "AmericanOption.h"
//
//int main()
//{

    //////////////////////// Partie 1 //////////////////////////////////////

    //try {
    //    std::cout << "=== TEST: Black-Scholes Vanilla vs Digital Options ===\n\n";

    //    // --- Market parameters ---
    //    double S = 100.0;   // spot price
    //    double r = 0.05;    // interest rate
    //    double sigma = 0.2; // volatility
    //    double T = 1.0;     // time to expiry (in years)
    //    double K = 100.0;   // strike

    //    // --- Create Vanilla options ---
    //    CallOption callOpt(T, K);
    //    PutOption  putOpt(T, K);

    //    auto vanillaCall = BlackScholesPricer::ForVanilla(&callOpt, S, r, sigma);
    //    auto vanillaPut = BlackScholesPricer::ForVanilla(&putOpt, S, r, sigma);

    //    // --- Create Digital options ---
    //    EuropeanDigitalCallOption digitalCall(T, K);
    //    EuropeanDigitalPutOption  digitalPut(T, K);

    //    auto digitalCallPricer = BlackScholesPricer::ForDigital(&digitalCall, S, r, sigma);
    //    auto digitalPutPricer = BlackScholesPricer::ForDigital(&digitalPut, S, r, sigma);

    //    // --- Compute and display prices ---
    //    std::cout << ">>> Vanilla Options <<<\n";
    //    std::cout << "Call price = " << vanillaCall.priceVanilla() << std::endl;
    //    std::cout << "Put  price = " << vanillaPut.priceVanilla() << std::endl;

    //    std::cout << "\n>>> Digital Options <<<\n";
    //    std::cout << "Digital Call price = " << digitalCallPricer.priceDigital() << std::endl;
    //    std::cout << "Digital Put  price = " << digitalPutPricer.priceDigital() << std::endl;

    //    // --- Compare payoffs ---
    //    std::cout << "\n=== Payoff comparison at expiry ===\n";
    //    for (double S_test : {80.0, 100.0, 120.0}) {
    //        std::cout << "S = " << S_test
    //            << " | Vanilla Call: " << callOpt.payoff(S_test)
    //            << " | Digital Call: " << digitalCall.payoff(S_test)
    //            << " | Vanilla Put: " << putOpt.payoff(S_test)
    //            << " | Digital Put: " << digitalPut.payoff(S_test)
    //            << std::endl;
    //    }
    //}
    //catch (const std::exception& e) {
    //    std::cerr << "Exception: " << e.what() << std::endl;
    //}

    /////////////////////////  Partie 2 //////////////////////////////////////////////////
   
    //CallOption call(1.0, 100.0);
    //CRRPricer pricer(&call, 3, 100.0, 0.1, -0.05, 0.02);     // depth = 3 steps, S0 = 100, up = +10%, down = -5%, rate = 2%


    //// Using backward induction (default)
    //double price_tree = pricer();          // closed_form = false

    //// Using direct binomial closed form
    //double price_formula = pricer(true);

    //std::cout << "Part 2 \n";
    //std::cout << "Price (tree method): " << price_tree << std::endl;
    //std::cout << "Price (closed form): " << price_formula << std::endl;

    //pricer.displayTrees();



    //////////////////////// Partie 3  ////////////////////////////////////////
    //try {
    //    double expiry = 1.0;               // 1 year
    //    double strike = 100.0;             // strike price
    //    std::vector<double> timeSteps = { 0.25, 0.5, 0.75, 1.0 }; // quarterly steps

    //    // create Asian Call and Put options 
    //    AsianCallOption asianCall(expiry, strike, timeSteps);
    //    AsianPutOption  asianPut(expiry, strike, timeSteps);

    //    // simulated path of underlying asset prices (e.g., from Monte Carlo)
    //    std::vector<double> samplePath1 = { 95.0, 100.0, 105.0, 110.0 }; // increasing prices
    //    std::vector<double> samplePath2 = { 120.0, 110.0, 100.0, 90.0 }; // decreasing prices

    //    // test payoffPath()
    //    double callPayoff1 = asianCall.payoffPath(samplePath1);
    //    double putPayoff1 = asianPut.payoffPath(samplePath1);

    //    double callPayoff2 = asianCall.payoffPath(samplePath2);
    //    double putPayoff2 = asianPut.payoffPath(samplePath2);

    //    std::cout << "=== Asian Option Test ===\n";
    //    std::cout << "Average price (path 1) = "
    //        << (95 + 100 + 105 + 110) / 4.0 << "\n";
    //    std::cout << "Call Payoff (path 1) = " << callPayoff1 << "\n";
    //    std::cout << "Put  Payoff (path 1) = " << putPayoff1 << "\n\n";

    //    std::cout << "Average price (path 2) = "
    //        << (120 + 110 + 100 + 90) / 4.0 << "\n";
    //    std::cout << "Call Payoff (path 2) = " << callPayoff2 << "\n";
    //    std::cout << "Put  Payoff (path 2) = " << putPayoff2 << "\n\n";

    //    // --- Test type detection ---
    //    std::cout << "asianCall.isAsianOption() = " << std::boolalpha
    //        << asianCall.isAsianOption() << "\n";
    //    std::cout << "asianPut.isAsianOption()  = " << std::boolalpha // boolalpha tells the output stream to print true or false
    //        << asianPut.isAsianOption() << "\n";
    //}
    //catch (const std::exception& e) {
    //    std::cerr << "Error: " << e.what() << std::endl;
    //}

    ////// test du Monte Carlo Black-Scholes pricer ////
    //BlackScholesMCPricer mc(&call, 100.0, 0.05, 0.2);

    //mc.generate(100000); // on simule 100,000 chemins

    //std::cout << "MC estimated price = " << mc() << std::endl;

    //auto ci = mc.confidenceInterval();
    //std::cout << "95% confidence interval = [" << ci[0] << ", " << ci[1] << "]\n";

    //return 0;


    ///// Partie 4 ///////////////////////////
//    try {
//        std::cout << std::fixed << std::setprecision(4);
//        std::cout << "==============================\n";
//        std::cout << "     OPTION PRICING TESTS     \n";
//        std::cout << "==============================\n\n";
//
//        //parametre
//        double S0 = 100.0;       // spot price
//        double K = 100.0;        // strike
//        double r = 0.05;         // risk-free rate
//        double sigma = 0.2;      // volatility
//        double T = 1.0;          // maturity (1 year)
//        int N = 10;               // tree depth
//        int nbPaths = 200000;    // MC samples
//
//        // Option european
//        CallOption call(T, K);
//        PutOption  put(T, K);
//
//        std::cout << ">>> European Vanilla Options <<<\n";
//
//        // Black-Scholes Closed Form
//        BlackScholesPricer bsCall = BlackScholesPricer::ForVanilla(&call, S0, r, sigma);
//        BlackScholesPricer bsPut = BlackScholesPricer::ForVanilla(&put, S0, r, sigma);
//        std::cout << "Closed-form Call price = " << bsCall.priceVanilla() << "\n";
//        std::cout << "Closed-form Put  price = " << bsPut.priceVanilla() << "\n\n";
//
//        // Monte Carlo Pricing 
//        BlackScholesMCPricer mcCall(&call, S0, r, sigma);
//        BlackScholesMCPricer mcPut(&put, S0, r, sigma);
//        mcCall.generate(nbPaths);
//        mcPut.generate(nbPaths);
//
//        auto ciCall = mcCall.confidenceInterval();
//        auto ciPut = mcPut.confidenceInterval();
//
//        std::cout << "Monte Carlo (N=" << nbPaths << ")\n"; // on verifie les valeurs de Monte Carlo et si l'intervalle et bien dans la val
//        std::cout << "MC Call price = " << mcCall() << "  CI: [" << ciCall[0] << ", " << ciCall[1] << "]\n"; //lower and upper bounds of the 95% confidence interval
//        std::cout << "MC Put  price = " << mcPut() << "  CI: [" << ciPut[0] << ", " << ciPut[1] << "]\n\n";
//
//        //CRR Binomial Approximation 
//        CRRPricer crrCall(&call, N, S0, r, sigma); // using BS(black scholes) approximation
//        CRRPricer crrPut(&put, N, S0, r, sigma);
//
//        double crrCallPrice = crrCall();
//        double crrPutPrice = crrPut();
//
//        std::cout << "CRR Binomial (N=" << N << ")\n";
//        std::cout << "CRR Call price = " << crrCallPrice << "\n";
//        std::cout << "CRR Put  price = " << crrPutPrice << "\n\n"; // on verifie si les valeurs du CRR se rapprochent du closed form
//
//        //  American Options
//        std::cout << ">>> American Options <<<\n";
//
//        AmericanCallOption amerCall(T, K);
//        AmericanPutOption  amerPut(T, K);
//
//        CRRPricer amerCallPricer(&amerCall, N, S0, r, sigma);
//        CRRPricer amerPutPricer(&amerPut, N, S0, r, sigma);
//
//        amerCallPricer.compute();
//        amerPutPricer.compute();
//
//        double amerCallPrice = amerCallPricer();
//        double amerPutPrice = amerPutPricer();
//
//        std::cout << "American Call Price = " << amerCallPrice << "\n"; // le call Americain devrait etre egal au call europeen?
//        std::cout << "American Put  Price = " << amerPutPrice << "\n\n";
//
//        //Display Early Exercise Policy for the American Put 
//        std::cout << "Early Exercise Tree (1 = exercise, 0 = hold):\n"; // la derniere ligne avec que des 0 correspond a l'echance de l'Option
//        for (int n = 0; n <= N; ++n) {
//            std::cout << "Step " << n << ": ";
//            for (int i = 0; i <= n; ++i) {
//                std::cout << (amerPutPricer.getExercise(n, i) ? "1 " : "0 ");
//            }
//            std::cout << "\n";
//        }
//
//        //  display value trees visually ===
//        std::cout << "\nDisplaying CRR Trees for American Put...\n";
//        amerPutPricer.displayTrees(); 
//
//        std::cout << "\nAll tests executed successfully \n";
//    }
//    catch (const std::exception& e) {
//        std::cerr << "Error: " << e.what() << std::endl;
//    }
//
//
//}

#include <iostream>
#include "CallOption.h"
#include "PutOption.h"
#include "EuropeanDigitalCallOption.h"
#include "EuropeanDigitalPutOption.h"
#include "BlackScholesPricer.h"
#include "CRRPricer.h"
#include "BinaryTree.h"


int main() {
    {

        double S0(95.), K(100.), T(0.5), r(0.02), sigma(0.2);
        CallOption opt1(T, K);
        PutOption opt2(T, K);


        std::cout << "European options 1" << std::endl << std::endl;

        {
            BlackScholesPricer pricer1(&opt1, S0, r, sigma);
            std::cout << "BlackScholesPricer price=" << pricer1() << ", delta=" << pricer1.delta() << std::endl;

            BlackScholesPricer pricer2(&opt2, S0, r, sigma);
            std::cout << "BlackScholesPricer price=" << pricer2() << ", delta=" << pricer2.delta() << std::endl;
            std::cout << std::endl;
        }
    }
}
