#include <iostream>
#include "lib/flang.hpp"

using namespace std;
using namespace flang::monads;

int main() 
{
    auto times2 = flang::$f [](auto a) { return 2 * a; };
    auto sum = flang::$f [](auto a) {
        return [a](auto b) {
            return a + b;
        };
    };

    auto some_f = Some(sum(2));
    auto some_arg = Some(times2(2));

    auto maybe_f_arg = some_f.apply(some_arg);
    auto maybe_map_f_arg = maybe_f_arg.map(times2);

    cout << maybe_map_f_arg.unwrap() << endl;
    return 0;
};