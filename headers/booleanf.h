#ifndef BOOLEANF_H
#define  BOOLEANF_H

const auto Void = []() { return ([](){ })(); };

const auto True = [](auto x) {
    return [x](auto y) { return x; };
};

const auto False = [](auto x) {
    return [x](auto y) { return y; };
};

const auto to_boolean = [](auto p) {
    return p(true)(false);
};

// operadores

const auto andf = [](auto p){
    return [p](auto q) {
        return p(q)(False);
    };
};


const auto orf = [](auto p) {
    return [p](auto q) {
        return p(True)(q);
    };
};


const auto notf = [](auto p) {
    return p(False)(True);
};

// condicionais

const auto if_then_or = [](auto p) {
    return [p](auto then) {
        return [p, then](auto or_then) {
            return p(then)(or_then)();
        };
    };
};

const auto if_then = [](auto p) {
    return [p](auto then) {
        return p(then)(Void)();
    };
};

const auto lift = [](bool native) {
    return [native](auto t, auto r) {
        return (native ? t : r)();
    };
};

#endif