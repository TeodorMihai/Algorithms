#include <bits/stdc++.h>

using namespace std;

ifstream fin("ciur.in");
ofstream fout("ciur.out");

const int NMAX = 2e6 + 6;

int n;
bool ciur[NMAX];
int primes;

int main() {

	fin >> n;


	for(int i = 2; i <= n ; ++i) {

		if(ciur[i] == 0) {

			primes++;

			for(int j = i + i ; j <= n; j += i)
				ciur[j] = 1;
		}
	}

	fout << primes << '\n';

	return 0;

}