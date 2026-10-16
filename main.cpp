#include <iostream>
#include "headers/booleanf.h"
#include "headers/numbersf.h"
#include "headers/wrappersf.h"
#include "headers/operatorsf.h"

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
    auto neg_num = Dec(Zero);

    cout << to_int(num) << endl;
    cout << to_int(neg_num) << endl;


    auto sum = Add(Inc(Zero))(Inc(Zero));
    auto sub = Sub(Inc(Inc(Zero)))(Inc(Zero));
    auto times = Times(Inc(Inc(Zero)))(Inc(Inc(Inc(Zero))));

    cout << to_int(sum) << endl;
    cout << to_int(sub) << endl;
    cout << to_int(times) << endl;

    auto some = Some(Zero);
    auto none = None;
    
    auto st = is_some(some);
    auto nt = is_some(none);

    auto ntt = is_none(none);
    auto nst = is_none(some);

    cout << "========\n" << "some/none" << endl;
    cout << to_boolean(ntt) << endl;
    cout << to_boolean(nst) << endl;

    cout << to_boolean(st) << endl;
    cout << to_boolean(nt) << endl;

    cout << "teste soma fmap" << endl;
    auto finc_n = fmap(Inc)(None);
    auto finc_s = fmap(Inc)(Some(Zero));

    
    auto nfinc = "não é possível operar em cima de None";
    auto sfinc = "O resultado da operações é: ";
    auto rnmsg = if_then_or(is_some(finc_n))
        ([nfinc]() { return nfinc; })
        ([sfinc, finc_s]() { 
            return to_int(unwrap(finc_s)); 
        });

    cout << rnmsg() << endl;

    auto fc = Some(Zero) > fmap(Inc);
    auto incc = Zero > Inc > Inc;

    cout << to_int(incc) << endl;
    cout << to_int(unwrap(fc)) << endl;

    return 0;
}