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

            template <typename U, typename F>
            constexpr auto map(F f) const {
                return this->has_value 
                    ? Maybe<U>(f(this->value)) 
                    : Maybe<U>();
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