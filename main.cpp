#include <iostream>
#include "headers/booleanf.hpp"

using namespace std;

int main()
{ 
    auto cast = (fnot >> fnot) $ Bool(10 < 2);
    auto b = to_cpp_bool $ cast;
    cout << b << endl;

    cout << ter << endl;
    return 0;
};