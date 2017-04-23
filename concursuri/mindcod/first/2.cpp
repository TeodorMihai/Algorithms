#include <bits/stdc++.h>

using namespace std;

const long long MOD = 666013;
const long long NMAX = 1e5 + 5;

int main() {

	long long n, m;
	cin >> n >> m;

	if(m > n || m == 1) {

		cout << 0 << '\n';
		return 0;
	}

	long long res = 1;

	for(int i = 1; i <= (m - 1); ++i)
		res = (res * i) % MOD;
	long long mf = 1;
	for(int i = 1 ; i <= m ; ++i) {
		res = (res * i) % MOD;
		mf = (mf * i) % MOD;
	}

	for(int i = 1; i <= n - m; ++i) {
		res = (res * n) % MOD;
	}
	cout << res << '\n';

	return 0;
}