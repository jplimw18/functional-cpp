#include <iostream>
#include "lib/flang.hpp"

using namespace std;

constexpr auto id = f [](auto a) { return a; };
constexpr auto _const = f [](auto a) { return [a](auto b) { return a; }; };
constexpr auto flip = f [](auto g) { 
    return [g](auto b) { 
        return [g, b](auto a) {
            return g(a)(b);
        };
    };
};

constexpr auto a = [](int a) {
    return a;
};

constexpr auto b = [](auto x) {
    return x;
};

constexpr auto c = [](int x, int y) {
    return x + y;
};


int main() 
{           
    // auto fa = _const(1);
    // auto fb = fa(3);
    // cout << fb << endl;

    // auto raw = [](auto x) { return x; };
    // static_assert(IsUnary<Fn<decltype(raw)>>);

    // auto fa = id >> _const;
    // auto fa_1 = fa(5);
    // auto fa_2 = fa_1(2);

    // cout << fa_2 << endl;

    auto c = _const(1);
    auto ci = _const(1) >> id;
    auto ic = id >> _const;
    auto ice1 = ic(_const);
    auto ice2 = ice1(id);
    auto ice3 = ice2(2);
    auto ice4 = ice3(4);

    cout << ice4 << endl;

    auto fc = flip(_const);
    return 0;
};