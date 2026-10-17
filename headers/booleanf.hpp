#ifndef BOOLEANF_H
#define BOOLEANF_H

#include "typesf.hpp"

// base
constexpr auto Bool = f [](bool native) {
    return f [native](auto x) {
        return f [native, x](auto y) {
            return native ? x : y;
        };
    };
};

const auto True = Bool(true);
const auto False = Bool(false);


// opeardores

constexpr auto fand = f [](auto p) {
    return f [p](auto q) {
        return p $ q $ False;
    };
};

constexpr auto ffor = f [](auto p) {
    return f [p](auto q) {
        return (p $ True) $ q;
    };
};

constexpr auto fnot = f [](auto p) {
    return p(False)(True);
};


constexpr auto if_then = f [](auto c) {
    return f [c](auto ft) {
        return f [c, ft](auto fnt) {
            return c(ft)(fnt);
        };
    };
};

// conversor nativo

constexpr auto to_cpp_bool = f [](auto b) {
    return (b $ true $ false);
};


#endif