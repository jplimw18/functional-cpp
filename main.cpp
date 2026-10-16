#include <iostream>
#include "headers/booleanf.h"
#include "headers/numbersf.h"

using namespace std;


int main()
{
    auto a = fnot(False);
    auto b = fnot(True);

    cout << to_boolean(a) << " " << to_boolean(b) << endl;

    auto c = fand(False)(False);
    auto d = fand(False)(True);
    auto e = fand(True)(False);
    auto f = fand(True)(True);

    cout 
    << to_boolean(c) << " " 
    << to_boolean(d) << " "
    << to_boolean(e) << " "
    << to_boolean(f) << " "
    << endl;

    auto g = ffor(False)(False);
    auto h = ffor(False)(True);
    auto i = ffor(True)(False);
    auto j = ffor(True)(True);

    cout 
    << to_boolean(g) << " " 
    << to_boolean(h) << " "
    << to_boolean(i) << " "
    << to_boolean(j) << " "
    << endl;


    auto k = if_then_or(True)(False)(True);

    cout << to_boolean(k) << endl;

    auto num = Inc(Inc(Zero));

    cout << to_int(num) << endl;
    return 0;
}