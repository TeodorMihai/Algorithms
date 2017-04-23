#include <bits/stdc++.h>
 
using namespace std;
 
const int NMAX = 1e5 + 5;
const int INF = 0x3f3f3f3f;
 
int n; int m;
int aib[NMAX];
int v[NMAX];
 
int query(int, int);
 
int bit(int x) { return x & -x; }
 
void change(int pos, int value) {
 
    v[pos] = value;
 
    for(int x = pos ; x <= n ; x += bit(x)) {
 
        if(aib[x] == pos) {
 
            int newMaxim = query(x - bit(x) + 1, x - 1);//log N, special query
            aib[x] = v[x] > v[newMaxim] ? x : newMaxim;
 
        } else
            aib[x] = v[pos] > v[aib[x]] ? pos : aib[x];
    }
}
 
int query(int st, int dr) {
 
    int maxInd = 0;
    int potential = 0;
    for(int pos = dr; pos >= st; ) {
 
        if(pos - bit(pos) + 1 < st) { //nu pot face query
            potential = pos;
            pos--;
        } else {
            potential = aib[pos];
            pos -= bit(pos);
        }
 
        if(v[potential] > v[maxInd])
            maxInd = potential;
    }
 
    return maxInd;
}
 
int main() {
 
    freopen("arbint.in", "r", stdin);
    freopen("arbint.out", "w", stdout);
 
   scanf("%d%d", &n, &m);
 
    int a, b;
 
    for(int i = 1; i <= n ; ++i) {
    	scanf("%d", v + i);
        change(i, v[i]);
    }
 
    int t;
 
    aib[0] = -INF;
 
    for(int i = 1; i <= m ; ++i) {
 	
 		scanf("%d%d%d", &t, &a, &b);
        if(t == 0) cout << v[query(a, b)] << '\n';
        if(t == 1) change(a, b);
    }
 
    return 0;
}