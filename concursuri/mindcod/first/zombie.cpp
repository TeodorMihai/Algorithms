#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5 + 5;
const int MOD = 666013;

int n;
int d[NMAX];

int fact[NMAX];

//a ^ MOD - 2
int inv(int a) {
 
    int put[32];
 
    put[0] = a;
 
    for(int i = 1; i < 32; ++i)
        put[i] = (1ll * put[i - 1] * put[i - 1]) % MOD;
 
    int rez = 1;
    for(int i = 0 ; i < 32; ++i)
        if( (1 << i) & (MOD - 2))
            rez = (1ll * rez * put[i]) % MOD;
 
    return rez;
}
 
int comb(int a, int b) {
 
    //a! / b! * (a - b)!
    return 1ll * fact[a] * inv(fact[b]) % MOD * inv(fact[a - b]) % MOD;
}

int main() {

	d[1] = 0;
	d[2] = 1;
	
	cin >> n;
	fact[1] = 1;
	fact[0] = 1;

	for(int i = 1 ; i < NMAX; ++i)
		fact[i] = fact[i - 1] * i;

	for(int i = 3; i <= n; ++i)
		d[i] = (1ll * (i - 1) * (d[i - 2] + d[i - 1])) % MOD;

	int s = 0;
	for(int k = 1; k <= n; ++k)
		s = (1ll * s + 1ll * comb(n, k) * fact[n - k]) % MOD;
	s = (fact[n] - s) % MOD;
	if(s < 0)
		s += MOD;

	cout << d[n] << '\n' << s << '\n';

	return 0;

}