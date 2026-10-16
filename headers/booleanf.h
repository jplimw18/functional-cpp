#ifndef BOOLEANF_H
#define BOOLEANF_H

// wrapper do tipo (pensar em algo melhor depois)
template <typename F>
const F __bool__(F& f) { return f; }

const auto __true__ = [](auto x) {
    return [x](auto y) { return x; };
};

const auto __false__ = [](auto x) {
    return [x](auto y) { return y; };
};

const auto True = __bool__(__true__);
const auto False = __bool__(__false__);

// OPERADORES

constexpr auto fnot(auto p) {
    return p(False)(True);
};

constexpr auto fand(auto p) {
    return [p](auto q) {
        return p(q)(False);
    };
};

constexpr auto ffor(auto p) {
    return [p](auto q) {
        return p(True)(q);
    };
};

// CONDICIONAIS

constexpr auto if_then_or(auto condition) {
    return [condition](auto then) {
        return [condition, then](auto then_or) {
            return condition(then)(then_or);
        };
    };
};

// CONVERSORES NATIVOS
constexpr auto to_boolean(auto p) {
    return p(true)(false);
};

#endif