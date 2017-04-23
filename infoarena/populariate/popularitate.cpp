#include <bits/stdc++.h>

using namespace std;

ifstream fin("popularitate.in");
ofstream fout("popularitate.out");

const int KMAX = 1e7 + 5;
const int MMAX = 102;
const int NMAX = 1005;

int k; int m; 
vector<int> primes;
vector<int> put;
int numara[40];


//O(sqrt(x))
void decompose(int x) {

	for(int i = 2; i * i <= x; ++i) {

		bool divisible = false;
		int cn = 0;
		while(x % i == 0) {
			x /= i;
			divisible = true;
			cn++;
		}

		if(divisible)
			primes.push_back(i), put.push_back(cn);

	}

	if(x > 1) {
		primes.push_back(x);
		put.push_back(1);
	}
}

void cnt(int x) {

	for(int i = 0 ; i < primes.size(); ++i) {

		while(x % primes[i] == 0)
			numara[i]++, x /= primes[i];

		if(x < primes[i]) break;
	}

}

int main() {

	fin >> k;

	decompose(k);

	fin >> m;

	int maxPop = 0;
	int bestGr = 1;

	for(int i = 1; i <= m ; ++i) {

		int nr; fin >> nr;
		memset(numara, 0, sizeof numara);

		for(int j = 1; j <= nr; ++j) {
			int x; fin >> x;
			cnt(x);
		}

		int mini = 0x3f3f3f;

		for(int i = 0 ; i < primes.size(); ++i)
			mini = min(mini, numara[i] / put[i]);

		if(mini > maxPop) {
			bestGr = i;
			maxPop = mini;
		}
	}

	fout << maxPop << ' ' << bestGr << '\n';

	return 0;
}