#ifndef NUMBERSF_H
#define NUMBERSF_H

#include "booleanf.h"

const auto Zero = [](auto f) {
    return [f](auto x) {
        return x;
    };
};

const auto __increment = [](auto number) {
    return [number](auto f) {
        return [number, f](auto x) {
            return (f(number(f)(x)));
        };
    };
};

const auto is_zero = [](auto number) {
    return number([](auto x) { return False; })(True);
};

const auto __pair = [](auto x) {
    return [x](auto y) {
        return [x, y](auto f) {
            return f(x)(y);
        };
    };
};

const auto First = [](auto p) {
    return p(True);
};

const auto Second = [](auto p) {
    return p(False);
};

const auto __foward_pair = [](auto p) {
    return __pair(Second(p))(__increment(Second(p)));
};

const auto __decrement = [](auto number) {
    return First(number(__foward_pair)(__pair(Zero)(Zero)));
};

const auto __create_integer = [](auto pos) {
    return [pos](auto neg) {
        return __pair(pos)(neg);
    };
};

constexpr auto __integer(int native) {
    if (native == 0)
        return Zero;

    return __increment(__integer(native -1));
};

const auto Integer = [](int n) {
    return (n > 0) 
        ? __create_integer(n)(0)
        : (n == 0)
        ? __create_integer(0)(0)
        : __create_integer(0)(n);
};

const auto to_uint = [](auto number) {
    auto increment = [](int n){ return n + 1; };
    return number(increment)(0);
};

const auto to_int = [](auto number) {
    auto p = to_uint(First(number));
    auto n = to_uint(Second(number));
    return p - n;
};

#endif