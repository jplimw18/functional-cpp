#ifndef OPERATORSF_H
#define OPERATORSF_H

#include <utility>

// Aplicacao (não sei o nome desse treco)
// tentei pegar o que o haskell usa para passagem de argumentos para uma funcao de alta ordem
struct AppProxy {};
constexpr AppProxy APPLY{};

template <typename T>
struct LHSAppProxy {
    T fn;

    constexpr explicit LHSAppProxy(T f) : fn(f) { }

    template <typename Args>
    constexpr auto operator >(Args&& args) const {
        return fn(std::forward<Args>(args));
    };
};

template <typename T>
constexpr LHSAppProxy<T> operator <(const T& fn, AppProxy) {
    return LHSAppProxy<T>(fn);
};

#define $ <APPLY>

// Composicao

struct ComposeProxy {};
constexpr ComposeProxy COMPOSE{};

template <typename T, typename U>
struct LHSComposeProxy {
    T lhs;
    U rhs;
    
    constexpr explicit LHSComposeProxy(T l, U r) : lhs(l), rhs(r) { }

    template <typename ... Args>
    constexpr auto operator()(Args&&... args) const {
        return rhs(lhs(std::forward<Args>(args)...));
    };
};

template <typename T, typename U>
constexpr auto operator >>(const T& lhs, const U& rhs) {
    return LHSComposeProxy<T,U>(lhs, rhs);
};

#endif