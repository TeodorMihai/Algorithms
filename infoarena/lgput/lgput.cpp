#include <bits/stdc++.h>

using namespace std;

ifstream fin("lgput.in");
ofstream fout("lgput.out");

const unsigned long long MOD = 1999999973;

unsigned long long n, p;//n ^ p 
unsigned long long put[35];
//put[i] = n ^ (2 ^ i)

int main() {

	fin >> n >> p;

	put[0] = n % MOD;

	for(int i = 1; i <= 32; ++i)
		put[i] =  put[i - 1] * put[i - 1] % MOD;

	unsigned long long ans = 1;

	for(int i = 0 ; i <= 32; ++i)
		if(p & (1ll << i)) {
			ans =  ans * put[i] % MOD;
		}
	fout << ans << '\n';
	return 0;
}