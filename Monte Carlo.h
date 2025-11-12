#pragma once
#include <random>
#include <mutex>

class MT {
private:
    std::mt19937 _gen;                          
    std::uniform_real_distribution<> _unif;     //  loi uniforme U(0,1)
    std::normal_distribution<> _norm;           // loi normale N(0,1)
    static MT* _instance;                       // instance unique
    static std::mutex _mutex;                   // thread safety

    MT() 
        : _gen(std::random_device{}()),
        _unif(0.0, 1.0),
        _norm(0.0, 1.0)
    {} // constructeur prive

public:
    MT(const MT&) = delete;
    MT& operator=(const MT&) = delete;

    static MT& instance() { // point d'acces singleton
        std::lock_guard<std::mutex> lock(_mutex);
        if (!_instance)
            _instance = new MT();
        return *_instance;
    }

    // fonction statique qui sert de raccourci vers une fonction interne plus complexe
    static double rand_unif() {
        return instance()._unif(instance()._gen);
    }

    static double rand_norm() {
        return instance()._norm(instance()._gen);
    }
};
