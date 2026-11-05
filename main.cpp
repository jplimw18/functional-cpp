#include <iostream>
#include "lib/flang.hpp"

using namespace std;
using namespace flang::monads;
using namespace flang::booleans;

int main() 
{
    auto sum = flang::$f [](auto a) {
        return [a](auto b) {
            return a + b;
        };
    };

    auto times = flang::$f [](auto a) {
        return [a](auto b) {
            return a * b;
        };
    };

    auto op = if_then<f_and(False)(True)>(sum)(times);

    cout << op(2)(3) << endl;

    return 0;
};