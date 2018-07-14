/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  18.04.2018 08:43:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <cstdlib>
#include <iostream>
using namespace std;

class C {
    int i;
public:
    C() : i(0) {
        cout << "D" << i;
    }
    C(int _i) : i(_i) {
        cout << "I" << i;
    }
    C(const C& _c) : i(_c.i) {
        cout << "C" << i;
    }
    C& operator= (const C& _c) {
        i = _c.i; cout << "c" << i; return *this;
    }
    C(C&& _c) : i(_c.i) {
        cout << "M" << i; _c.i = 0;
    }
    C& operator= (C&& _c) {
        i = _c.i; cout << "m" << i; _c.i = 0; return *this;
    }
    ~C() {
        cout << "d" << i;
    }
};

int main() {
  
    C c;
    c = 5;

}
