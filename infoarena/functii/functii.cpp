#include <bits/stdc++.h>

using namespace std;

ifstream fin("functii.in");
ofstream fout("functii.out");

const int MOD = 30103;
const int NMAX = 10002;

int fact[NMAX];

void euclid(int x, int y, int* a, int* b, int* d) {

	if(y == 0) {

		*a = 1;
		*b = 0;
		*d = x;

	} else {

		int a0; int b0;

		euclid(y, x % y, &a0, &b0, d);

		*a = b0;
		*b = 1ll * a0 - 1ll * b0 * (x / y);

	}
}


int invers(int x, int mod) {

	int a; int b; int d;
	
	euclid(x, mod, &a, &b, &d);

	a = a % mod;

	return a < 0 ? a + mod : a;
}


void precompute(int n, int mod) {

	fact[0] = 1;
	fact[1] = 1;

	for(int i = 1; i <= n; ++i)
		fact[i] = (1ll * fact[i - 1] * i) % mod;
}

int comb(int n, int k,int mod) {

	int res = fact[n] % mod;

	res = 1ll * res * invers(fact[k], MOD) % mod;
	res = 1ll * res * invers(fact[n - k], MOD) % mod;

	return res;
}

int main() {	

	int n; int s;
	
	fin >> n >> s ;

	precompute(n, MOD);

	int result = 0;

	for(int i = 1; i <= s - 1 ; ++i) {

		result = (1ll * result + (1ll * comb(n, i) * comb(n - i , s - i) ) % MOD) % MOD; 

	}	

	fout << result ; 
	

	return 0;
}