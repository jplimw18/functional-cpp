#ifndef FMONAD_H
#define FMONAD_H

namespace flang::monads {
    template <typename T>
    struct Maybe {
        private:
            T value;
            bool has_value;

        public:
            constexpr explicit Maybe(T v) : value(std::move(v)), has_value(true) { };
            constexpr explicit Maybe() : has_value(false) { };
    };

    template <typename T>
    Maybe(T) -> Maybe<T>;

    constexpr auto Some(auto &&value) {
        using T = decltype(value);
        return Maybe<std::decay_t<T>>(std::forward<T>(value));
    };
};

#endif