#ifndef NUMBERSF_H
#define NUMBERSF_H

// base
const auto __zero__ = f [](auto fn) {
    return f [fn](auto x) {
        return x;
    };
};

const auto __increment__ = f [](auto n) {
    return f [n](auto fn) {
        return [n, fn](auto x) {
            return fn(n $ fn $ x);
        };
    };
};

// pares para tentear fazer os numeros Interios

constexpr auto __pair__ = f [](auto x) {
    return f [x](auto y) {
        return [x,y](auto fn) {
            fn $ x $ y;
        };
    };
};

constexpr auto __first__ = f [](auto p) { return p $ True; };
constexpr auto __second__ = f[](auto p) { return p $ False; };

// Zero base
const auto Zero = __pair__ $ __zero__ $ __zero__;

constexpr auto Inc = f [](auto n) {
    auto first = __first__ $ n;
    auto second = __second__ $ n;

    return __pair__ $ (__increment__ $ first) $ second;
};

constexpr auto Dec = f [](auto n) {
    auto first = __first__ $ n;
    auto second = __second__ $ n;

    return __pair__ $ first $ (__increment__ $ second);
};

// conversores nativos

constexpr auto __uint__ = f [](auto n) {
    auto inc = [](auto count) { return count + 1; };
    return n(inc)(0);
};

constexpr auto to_cpp_int = f [](auto p) {
    int pos = __uint__ $ (__first__ $ p);
    int neg = __uint__ $ (__second__ $ p);

    return pos - neg;
};

// Tipo base Par puxar os int nativo para meu Int

constexpr auto Int = f [](int native) {
    
};

#endif