#include <iostream>
#include "headers/booleanf.h"
#include "headers/numbersf.h"

using namespace std;


int main()
{
    auto t_msg = []() { return "receba"; };
    auto f_msg = []() { return "bill"; };
    
    auto ten = Integer(10);
    auto ten_int = to_int(ten);
    return 0;
}