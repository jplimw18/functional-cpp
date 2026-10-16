#ifndef WRAPPERF_H
#define WRAPPERF_H

#include "booleanf.h"

const auto Void = []() { return ([]() { })(); };


// TIPOS BASE
template <typename F>
const F __maybe__(F& f) { return f; };


const auto __none__ = [](auto fn) {
    return [](auto none) { return none; };
};

const auto __some__ = [](auto s) {
    return [s](auto fn) {
        return [s, fn](auto none) { return fn(s); };
    };
};

const auto Some = __maybe__(__some__);
const auto None = __maybe__(__none__);


// VERIFICADORES
constexpr auto is_some(auto m) {
    return m([](auto x) { return True; })(False);
};

constexpr auto is_none(auto m) { return fnot(is_some(m)); };


// desempacota legal

constexpr auto unwrap(auto m) {
    return m([](auto s) { return s; })(Void);
};

constexpr auto unwrap_or(auto m) {
    return [m](auto d) {
        return m([](auto s) { return s; })(d);
    };
};


// OPERADORES

constexpr auto fmap(auto f) {
    return [f](auto m) {
        return m([f](auto s) { return Some(f(s)); })(None);
    };
};

#endif