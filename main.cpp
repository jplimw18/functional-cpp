#include <iostream>
#include "lib/flang.hpp"

using namespace std;

constexpr auto id = f [](auto a) { return a; };
constexpr auto _const = f [](auto a) { return [a](auto b) { return a; }; };
constexpr auto flip = f [](auto g) { 
    return [g](auto b) { 
        return [g, b](auto a) {
            g(a)(b);
        };
    };
};

int main() 
{           
    auto c = _const(1)(2); // 2
    auto ci = _const(1) >> id; // g (f b)
    auto ic = id >> _const; // id(1) -> const(1) -> f b -> 1
    return 0;
};