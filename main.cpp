#include <iostream>
#include "lib/flang.hpp"

using namespace std;
using namespace flang::monads;

int main() 
{           
    constexpr auto sum = flang::$f [](auto a) {
        return [a](auto b) {
            return a + b; 
        };
    };

    auto a = flang::monads::Maybe<int>();
    auto some = flang::monads::Some(10);

    return 0;
};