#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("drumuri3.in");
ofstream fout("drumuri3.out");
 
const int NMAX = 102;
const int MOD = 10007;
 
int n; int m; int k; int q;
 
int g[NMAX][NMAX];
int query[NMAX][NMAX];
int unit[NMAX][NMAX];

int b[NMAX][NMAX];
int a[NMAX][NMAX];
int c[NMAX][NMAX];
int d[NMAX][NMAX];

void read() {
 
    fin >> n >> m >> k >> q;
 
    for(int i = 1; i <= m; ++i) {
 
        int x; int y;
        fin >> x >> y;
        g[x][y] = 1;
        g[y][x] = 1;
    }

    for(int i = 1 ; i <= n ; ++i)
        unit[i][i] = 1;
}


 
void cpy(int a[][NMAX], int b[][NMAX]) {
 
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            a[i][j] = b[i][j];
}

 
void inm(int res[][NMAX], int a[][NMAX]) {
    
    for(int i = 1; i <= n ; ++i)
        for(int j = 1 ; j <= n ; ++j) {
            d[i][j] = 0;
            for(int k = 1; k <= n; ++k) 
                d[i][j] = (d[i][j] + res[i][k] * a[k][j]) % MOD;
        }
    cpy(res, d);
}

void add(int res[][NMAX], int a[][NMAX]) {

    for(int i = 1; i <= n ; ++i)
        for(int j = 1; j <= n ; ++j) {
            res[i][j] = res[i][j] + a[i][j];

            if(res[i][j] >= MOD)
                res[i][j] -= MOD;
        }
}

void printMatrix(int a[][NMAX]) {

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n ; ++j)
            cout << a[i][j] << ' ' ;
        cout << '\n'; 
    }
}


void compute(int dist) {

    // b = g ^ 1 + g ^ 2 + g ^ 3 + ... + g ^ dist
    //a = g ^ dist
    // dist = par => b ^ dist = (g^(dist/2) + I)* (b^(dist/2))
    // dist = impar => b ^ dist = (g^(dist-1/2) + I) * (b^(dist-1/2)) + g^(dist-1/2)^2 * g

    if(dist == 1) {
        cpy(b, g);
        cpy(a, g);
        return;
    }


    compute(dist/2);

    if(dist % 2 == 0) {
        cpy(c, a); 
        add(c, unit); inm(c, b);
        cpy(b, c);
        inm(a, a);
    } else {
        cpy(c, a); 
        add(c, unit); inm(c, b);

        inm(a, a);
        inm(a, g);

        add(c, a);
        cpy(b, c);
    }
}
 
void solve() {
    //R: g^1 + g^2 + g^3 + ... + g^k
    compute(k - 1);
    cpy(query, b);
}
 
void print() {
 
    while(q--) {
         
        int x; int y;
        fin >> x >> y;
        fout << query[x][y] << '\n';
    }
}
 
int main() {
 
    read();
 
    solve();
 
    print();
 
    return 0;
}