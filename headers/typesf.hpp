#ifndef TYPESF_H
#define TYPES_H

#include <utility>

// TIPO BASE
template <typename T>
struct Fn {
    T fn;

    constexpr explicit Fn(T fn) : fn(std::forward<T>(fn)) { };

    template <typename... Args>
    constexpr decltype(auto) operator()(Args&&... args) const & {
        return fn(std::forward<Args>(args)...);
    };

    template <typename... Args>
    constexpr decltype(auto) operator()(Args&&... args) && {
        return std::move(fn)(std::forward<Args>(args)...);
    };
};

// DEDUCAO DE YTIPOS

template <typename T>
Fn(T) -> Fn<T>;

// PROXYS

struct AppProxy {};
constexpr AppProxy APPLY{};
#define $ <APPLY>

template <typename T>
struct LHSAppProxy {
    T fn;
    constexpr explicit LHSAppProxy(T fn) : fn(std::forward<T>(fn)) { }

    template <typename Args>
    constexpr auto operator >(Args&& args) const {
        return fn(std::forward<Args>(args));
    }
};

// Sobrecarga para o operador < aceitar 
template <typename F>
constexpr auto operator <(const Fn<F>& fn, AppProxy) {
    return LHSAppProxy<Fn<F>>(fn);
};

// COMPISCAO

template <typename T, typename U>
constexpr auto operator >>(const Fn<T>& lhs, const Fn<U>& rhs) {
    return Fn([l = lhs.fn, r = rhs.fn](auto&&... args) {
        return r(l(std::forward<decltype(args)>(args)...));
    });
};


// WRAP
struct FnWrapProxy {};
constexpr FnWrapProxy FWRAP{};
#define f FWRAP<<

template <typename T>
constexpr auto operator <<(FnWrapProxy, T&& fn) {
    return Fn<std::decay_t<T>>(std::forward<T>(fn));
};

#endif