#ifndef FTYPES_H
#define FTYPES_H

#include <utility>
#include <concepts>


// definindo as traits para garantir funcoes unárias
template <typename T>
struct is_unary_trait {
    static constexpr std::size_t arity = 0;
    static constexpr bool is_unary = false;
};

template <typename ClassType, typename ReturnType, bool NExcept, typename... Args>
struct is_unary_trait<ReturnType(ClassType::*)(Args...) const noexcept(NExcept)> {
    static constexpr std::size_t arity = sizeof ...(Args);
    static constexpr bool is_unary = arity == 1;
};

template <typename ClassType, typename ReturnType, bool NExcept, typename... Args>
struct is_unary_trait<ReturnType(ClassType::*)(Args...) noexcept(NExcept)> {
    static constexpr std::size_t arity = sizeof ...(Args);
    static constexpr bool is_unary = arity == 1;
};

// auxiliar para barrar tipos que não tenham operator() 
// isso me garante (talvez) que eu consiga detectar tipos que não sejam funções entrando na minha Fn
// o problema é que não da para verificar o número de argumentos (a função precisa ser chamada, quando se trata de genérico)
// ^ esse problema eu resolve no operator() de fn, vale conferir e mais tarde pensar em alo que possa me relevar os args antes de precisar chamar a funcao
struct FnOperatorInjection { void operator()(); };
template <typename F>
struct FnTest : F, FnOperatorInjection { };

template <typename F> 
concept HasExplicitUnaryOperator = requires  { &F::operator(); } && is_unary_trait<decltype(&F::operator())>::is_unary;

template <typename F>
concept HasHiddenOperator = !requires { &F::operator(); } && std::is_class_v<F> && !requires { &FnTest<F>::operator(); };


template <typename F>
concept IsUnary = HasExplicitUnaryOperator<F> 
|| HasHiddenOperator<F>;

// outro helper para verificar se um T é um Fn<> para que eu saiba quando evelopar ou não um resultaoo
template <typename F>
requires IsUnary<F>
struct Fn;

template <typename T>
struct is_fn_instance : std::false_type { };

template <typename T>
struct is_fn_instance<Fn<T>> : std::true_type { };

template <typename T>
inline constexpr bool is_fn_instance_v = is_fn_instance<T>::value;



// meu tipo base tentando centralizar algo para que o compilador não chore
template <typename F>
requires IsUnary<F> // meu teste para rejeitar em tempo de compilação qualquer coisa que não seja uma função
struct Fn {
    F func;
    
    constexpr explicit Fn(F fn) : func(std::move(fn)) { };
    
    
    template <typename... Arg>
    requires (sizeof... (Arg) == 1) && std::invocable<decltype(func), Arg...>
    constexpr decltype(auto) operator()(Arg&&... arg) const & {
        auto r = func(std::forward<Arg>(arg)...);
        using T = decltype(r);
        if constexpr (IsUnary<T> && !is_fn_instance_v<T>){ return Fn<T>(r); }
        else return r;
    };
    
    template <typename... Arg>
    requires (sizeof... (Arg) == 1) && std::invocable<decltype(func), Arg...>
    constexpr decltype(auto) operator()(Arg&&... arg) && {
        
        auto r = std::move(func)(std::forward<Arg>(arg)...);
        using T = decltype(r);
        if constexpr (IsUnary<T> && !is_fn_instance_v<T>) { return Fn<T>(r); }
        else return r;
    };
};

template <typename T>
Fn(T) -> Fn<T>;


// para facilitar a declaracao de fn, assim fica mais bonito de criar as funç~eos (eu acho)
struct FnWrapProxy {};
constexpr FnWrapProxy FWRAP{};
#define f FWRAP<<

template <typename T>
constexpr auto operator <<(FnWrapProxy, T&& fn) {
    return Fn<std::decay_t<T>>(std::forward<T>(fn));
};

// $ para applicar funcoes (tentei abvordar algo parecido com o que vi de haskell)
struct AppProxy {};
constexpr AppProxy APP{};
#define $ <APP>

template <typename T>
struct LHSAppProxy {
    T lhs;
    
    constexpr explicit LHSAppProxy(T l) : lhs(std::forward<T>(l)) { };
    
    template <typename... Arg>
    requires (sizeof... (Arg) == 1)
    constexpr decltype(auto) operator>(Arg&&... args) const {
        return lhs(std::forward<Arg>(args)...);
    };
};

template <typename F>
constexpr decltype(auto) operator<(const Fn<F>& lhs, AppProxy) {
    return LHSAppProxy<Fn<F>>(lhs);    
};



// >> composição :D

template <typename F, typename G>
constexpr decltype(auto) operator >>(const Fn<F>& fn, const Fn<G>& gn) {
    return f [l = fn.func, r = gn.func](auto&&... args) {
        auto result = r(l(std::forward<decltype(args)>(args)...));
        using T = decltype(result);
        if constexpr (IsUnary<T> && !is_fn_instance_v<T>) { return Fn<T>(result); }
        else return result;
    };
};

#endif