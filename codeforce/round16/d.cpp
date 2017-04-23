#include <bits/stdc++.h>

using namespace std;

int euclid(int a, int b, int* x, int* y) {
 
    if(b == 0) {
         
        *x = 1;
        *y = 0;
        return a;
 
    } else {
 
        int y0;
        int x0;
 
        int d = euclid(b, a % b, &x0, &y0);
         
        int c = a / b;
 
        *x = y0;
        *y = x0 - c * y0;
        return d;
    }
}

int main() {
    //2 mod 5
    //5 mod 7

    int m1, m2;
    euclid(5, 7, &m1, &m2);

    cout << 2 * m2 * 7 + 5 * m1 * 5 << '\n';
}