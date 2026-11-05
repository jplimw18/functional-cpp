#ifndef FBOOLEAN_H
#define FBOOLEAN_H

namespace flang::booleans {

    struct Foolean {
        struct Partial;

        using sel_t = Foolean (*)(Foolean, Foolean);
        sel_t selector;

        constexpr Foolean(sel_t s) : selector(s) { };

        constexpr Partial operator()(Foolean a) const;
    };
    
    struct Foolean::Partial {
        Foolean::sel_t selector;
        Foolean a;

        constexpr Foolean operator()(Foolean b) const { return selector(a, b); };
    };
        
    constexpr Foolean::Partial Foolean::operator()(Foolean a) const { return { selector, a }; };

    constexpr Foolean true_sel (Foolean a, Foolean) { return a; };
    constexpr Foolean false_sel (Foolean, Foolean b) { return b; };

    inline constexpr Foolean True { true_sel };
    inline constexpr Foolean False { false_sel };

    // operações

    constexpr auto f_not(Foolean p) {
        return p(False)(True);
    };

    constexpr auto f_and(Foolean p) {
        return [p](Foolean q) {
            return p(q)(False);
        };
    };

    constexpr auto f_or(Foolean p) {
        return [p](Foolean q) {
            return p(True)(q);
        };
    };

    // tentativa bizarra de enfiar um if_then aqui kk

    namespace helpers {
        // helpers para if then
        struct pick_true_path { 
            template <typename T, typename E> 
            constexpr T operator()(T t, E &&) const { 
                return std::forward<T>(t);
            };
        };

        struct pick_false_path {
            template <typename T, typename E> 
            constexpr E operator()(T &&, E e) const { 
                return std::forward<E>(e);
            };
        };
    };

    // nativo
    constexpr bool to_native_bool(Foolean p) {
        return p(True)(False).selector == true_sel;
    };


    template <Foolean B>
    using picker = std::conditional_t<to_native_bool(B), helpers::pick_true_path, helpers::pick_false_path>;

    template <Foolean P>
    constexpr auto if_then = flang::$f [](auto f) {
        return [f](auto g) {
            return picker<P>{}(f, g);
        };
    };
};

#endif