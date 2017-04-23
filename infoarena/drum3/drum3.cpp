#include <bits/stdc++.h>

using namespace std;

ifstream fin("drum3.in");
ofstream fout("drum3.out");

const int NMAX = 5005;
const int MOD = 30013;

int n; int k; int ans;

int fact[NMAX];
int p[32];

int inv(int x, int m) {

	p[0] = x % m;
	
	for(int i = 1; i < 32; ++i)
		p[i] = (p[i - 1] * p[i - 1]) % m;

	//x ^ ( m - 2 )

	int res = 1;

	for(int i = 0 ; i < 32; ++i)
		if( (1 << i) & (m - 2) ) 
			res = (res * p[i]) % m;

	return res;
}

int comb(int n, int k) {

	//n! / k! * (n - k)!
	//a / b mod M <=> a * x mod  M ai b * x = 1 mod M
	//little fermat: a ^ p = a mod p

	//b ^ MOD - 2
	//p[i] = b^(2^i)
	return (1ll * fact[n] * inv(fact[k], MOD)) % MOD * inv(fact[n - k], MOD) % MOD;
}


int main() {

	fin >> n >> k;
	
	fact[1] = fact[0] = 1;

	for(int i = 2 ; i <= n; ++i)
		fact[i] = fact[i - 1] * i % MOD;

	if(k % 2 == 0)
		ans = 2 * comb(n - 2, k / 2 - 1) * comb(n - 2, k /2) % MOD;
	else 
		ans = 2 * comb(n - 2, (k - 1) / 2) * comb(n - 2, (k - 1) / 2) % MOD;
	fout << ans << '\n';
	return 0;
}