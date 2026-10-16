#ifndef NUMBERSF_H
#define NUMBERSF_H

#include "booleanf.h"

// WRAPPER
template <typename F>
const F __number__(F& f) { return f; };


// operacao OPERACAO MINIMA
constexpr auto __increment__(auto x) {
    return [x](auto f) {
        return [x, f](auto y) {
            return f(x(f)(y));
        };
    };
};


// UNIDADE MINIMA
constexpr auto __zero__ = [](auto f) { 
    return [f](auto x) { return x; };
};

const auto __d_zero__ = __number__(__zero__);

constexpr auto is_zero(auto x) {
    return x([](auto x) { return False; })(True);
};

// TENTANDO DEFINIR INTEIROs
constexpr auto __int_pair__ = [](auto x) {
    return [x](auto y) {
        return [x, y](auto f) {
            return f(x)(y);
        };
    };
};

constexpr auto __first__(auto p) { return p(True); };
constexpr auto __second__(auto p) { return p(False); };

constexpr auto __make_int_pair__(auto pos) {
    return [pos](auto neg) { return __int_pair__(pos)(neg); };
};

const auto Zero = __make_int_pair__(__d_zero__)(__d_zero__);

constexpr auto Inc = [](auto number) {
    return __make_int_pair__
        (__increment__(__first__(number)))
        (__second__(number));
};


constexpr auto Dec = [](auto number) {
    return __make_int_pair__
        (__first__(number))
        (__increment__(__second__(number)));
};



// OPERACOES

constexpr auto __add__(auto m) {
    return [m](auto n) {
        return [m, n](auto f) {
            return [f, m, n](auto x) {
                return m(f)(n(f)(x));
            };
        };
    };
};

constexpr auto __times__(auto m) {
    return [m](auto n) {
        return [m,n](auto f) {
            return m(n(f));
        };
    };
};

constexpr auto Add = [](auto a) {
    return [a](auto b) {
        auto x1 = __first__(a);
        auto y1 = __second__(a);
        auto x2 = __first__(b);
        auto y2 = __second__(b);

        return __make_int_pair__
            (__add__(x1)(x2))
            (__add__(y1)(y2));
    };
};



constexpr auto Sub = [](auto a) {
    return [a](auto b) {
        auto x1 = __first__(a);
        auto y1 = __second__(a);
        auto x2 = __first__(b);
        auto y2 = __second__(b);

        return __make_int_pair__
            (__add__(x1)(y2))
            (__add__(y1)(x2));
    };
};

constexpr auto Times = [](auto a) {
    return [a](auto b) {
        auto x1 = __first__(a);
        auto y1 = __second__(a);
        auto x2 = __first__(b);
        auto y2 = __second__(b);

        auto pos = __add__(__times__(x1)(x2))(__times__(y1)(y2));
        auto neg = __add__(__times__(x1)(y2))(__times__(y1)(x2));

        return __int_pair__(pos)(neg);
    };
};


// OPERADORES

// CONVERSOR NATIVO
constexpr auto to_uint(auto number) {
    auto inc = [](int counter) { return counter + 1; };
    return number(inc)(0);
};

constexpr auto to_int(auto number) {
    int pos = to_uint(__first__(number));
    int neg = to_uint(__second__(number));

    return pos - neg;
};

#endif