#ifndef FMONAD_H
#define FMONAD_H

namespace flang::monads {

    struct none_t { explicit constexpr none_t() = default; };

    template <typename T>
    struct Maybe {
        private:
            T value;
            bool has_value;

        public:
            constexpr explicit Maybe(T v) : value(std::move(v)), has_value(true) { };
            constexpr explicit Maybe() : has_value(false) { }; 

            constexpr Maybe(none_t) : has_value(false) { };

            bool is_some() const { return this->has_value; };
            bool is_none() const { return !this->has_value; };

            constexpr T& unwrap() & { return this->value; };
            constexpr T& unwrap() const & { return this->value; };

            template <typename F>
            requires flang::is_fn_instance_v<F>
            constexpr auto map(F f) const {
                using R = std::invoke_result_t<F,T>;
                return this->has_value 
                    ? Maybe<R>(f(this->value))
                    : Maybe<R>();
            };

            template <typename F>
            requires flang::is_fn_instance_v<F>
            constexpr auto map(Maybe<F>& f) {
                using R = std::invoke_result_t<F, T>;

                return this->has_value && f.is_some() 
                    ? Maybe<R>(f.unwrap()(this->value))
                    : Maybe<R>();
            };

            template <typename Arg>
            requires flang::is_fn_instance_v<T>
            constexpr auto apply(Maybe<Arg>& arg) {
                using R = std::invoke_result_t<T, Arg>;

                return this->has_value && arg.is_some() 
                    ? Maybe<R>(this->value(arg.unwrap()))
                    : Maybe<R>();
            };
    };

    template <typename T>
    Maybe(T) -> Maybe<T>;

    constexpr auto Some(auto &&value) {
        using T = decltype(value);
        return Maybe<std::decay_t<T>>(std::forward<T>(value));
    };

    inline constexpr none_t None { };
};

#endif