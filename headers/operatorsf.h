#ifndef OPERATORSF_H
#define OPERATORSF_H

template <typename T, typename F>
constexpr auto operator>(T&& val, F&& f) {
    return f(val);
};

#endif