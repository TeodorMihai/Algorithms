#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1000009;

int n; int k;

int c[NMAX];

int ciur[NMAX];

vector<int> primes;
vector<int> factK;

bool answer = false;

int main() {

	cin >> n >> k;

	int maxi = k;

	for(int i = 1; i <= n ; ++i) {
		cin >> c[i];
		if(maxi < c[i])
			maxi = c[i];
	}

	for(int i = 2; i * i <= maxi ; i++) {

		if(ciur[i] == 0)
			primes.push_back(i);

		for(int j = i + i ; j * j <= maxi; j += i)
			ciur[j] = 1;
	}

	int auxk = k;

	for(int i = 0 ; i < primes.size(); ++i) {

		int d = primes[i];

		int div = 1;
		while(auxk % d == 0) {
			auxk /= d;
			div = div * d;
		}

		factK.push_back(div);
	}

	if(auxk > 1)
		factK.push_back(auxk);

	for(int i = 1; i <= n && factK.size() > 0; ++i) {

		if(c[i] % k == 0) {
			factK.clear();
			break;
		}

		int auxk = c[i];

		for(int i = 0 ; i < primes.size(); ++i) {

			int d = primes[i];

			if(d > auxk)
				break;

			int div = 1;
			bool ok = false;

			while(auxk % d == 0) {
				auxk /= d;
				div = div * d;
				ok = true;
			}

			if(ok)
				for(int j = 0 ; j < factK.size(); ++j)
					if(div % factK[j] == 0) {
						factK.erase(factK.begin() + j);
						break;
					}

		}

		if(auxk > 1) {
			for(int j = 0 ; j < factK.size(); ++j)
					if(auxk % factK[j] == 0) {
						factK.erase(factK.begin() + j);
						break;
					}
		}

	}

	if(factK.size() == 0)
		cout << "Yes\n";
	else 
		cout << "No\n";

	return 0;
}