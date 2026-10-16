#ifndef NUMBERSF_H
#define NUMBERSF_H

#include "booleanf.h"

// WRAPPER
template <typename F>
const F __number__(F& f) { return f; };

// UNIDADE MINIMA
const auto __zero__ = [](auto f) { 
    return [f](auto x) { return x; };
};

// TENTANDO DEFINIR INTEIROS


// CONVERSOR NATIVO
constexpr auto to_int(auto number) {
    auto inc = [](int counter) { counter + 1; };
    return number(inc)(0);
};

#endif