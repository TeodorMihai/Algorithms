#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1000009;

int n; long long  k;

long long  c[NMAX];

int ciur[NMAX];

vector<int> primes;
vector<int> factK;

bool answer = false;


long long gcd(long long x, long long y) {

	if(y == 0)
		return x;
	return gcd(y, x % y);
}

int main() {

	cin >> n >> k;

	int maxi = k;

	for(int i = 1; i <= n ; ++i) {
		cin >> c[i];
		
	}

	if(n == 1) {

		if(k % c[1] == 0)
			cout << "Yes\n";
		else 
			cout << "No\n";
		return 0;
	}

	long long lcm = 1ll * c[1] * c[2] / gcd(c[1], c[2]);

	for(int i = 3; i <= n; ++i)
		lcm = 1ll * lcm * c[i] / gcd(lcm, c[i]);

	if(lcm % k == 0)
		cout << "Yes\n";
	else
		 cout << "No\n";

	return 0;
}