#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5 + 5;
const int MOD = 666013;

int n, m;
int fact[NMAX];
int d[NMAX];

//a^b
int put(int a, int b) {

	int res = 1;
	int p = a;

	for(int i = 1; i <= b; i <<= 1) {
		if(b & i)
			res = (1ll * res * p) % MOD;

		p = (1ll * p * p) % MOD;
	}

	return res;
}

void computeFact() {

	fact[0] = 1;
	for(int i = 1 ; i < NMAX ; ++i)
		fact[i] = (1ll * fact[i - 1] * i) % MOD;
}

//a^p = a mod p
int inv(int a) {
	//a * a^-1 == 1
	return put(a, MOD - 2);
}

int derangements(int m) {

	d[0] = 1;
	d[1] = 0;
	d[2] = 1;
	for(int i = 3; i <= m ; ++i)
		d[i] = 1ll * (i - 1) * (d[i - 2] + d[i - 1]) % MOD;

	return d[m];
}

int comb(int a, int b) {

	return 1ll * fact[a] * inv(1ll * fact[a - b] * fact[b] % MOD) % MOD;
}

int surjections(int n, int m) {

	//how to map n labeled  objects to m labeled sets, each sets contains smth
	//k! * stirling(n, m) =  sum(j = 0, m) (-1)^j * comb(m, j) * n^(m - j)
	//basically select j sets which don t receive anyhting, and after that assign
	//n elements on all possible remaining m - j sets
	//this works beacause sum(k = 0, n) com(n, k) * (-1)^k = 0 
	//exclusion inclusion principle

	int res = 0;

	for(int j = 0 ; j < m ; ++j) {

		if(j % 2 == 0)
			res = (1ll * res + 1ll * comb(m, j) * put(m - j, n)) % MOD;
		else 
			res = (1ll * res - 1ll * comb(m, j) * put(m - j, n)) % MOD;

		if(res < 0)
			res += MOD;
	}

	return res;

}

int main() {

	//freopen("zombie.in", "r", stdin);
	//freopen("zombie.out", "w", stdout);

	cin >> n >> m;

	if(n < m) {

		cout << 0 << '\n';
		return 0;
	}

	computeFact();
	cout << (1ll * surjections(n, m) * derangements(m) % MOD) << '\n';

	return 0;
}