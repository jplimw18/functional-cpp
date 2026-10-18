#include <iostream>
#include "lib/flang.hpp"

using namespace std;

constexpr auto id = [](auto a) { return a; };
constexpr auto _const = [](auto a) { return [a](auto b) { return a; }; };
constexpr auto flip = [](auto g) { 
    return [g](auto b) { 
        return [g, b](auto a) {
            g(a)(b);
        };
    };
};

struct Void {};

struct Test { void operator()(); };
template <typename F>
struct Deriv : F, Test { };


constexpr auto a = [](int a) {
    return a;
};

constexpr auto b = [](auto x) {
    return x;
};


int main() 
{           
    auto v = Fn<Void>(Void{});
    auto i = Fn<int>(2);
    auto fa = Fn(a);
    auto fid = Fn(id);
    return 0;
};