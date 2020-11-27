#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
using namespace std;

template<typename T>
class Test
{
    int v;
    public:
        Test(int v);
};
#include "../src/libtest.tpp"
#endif