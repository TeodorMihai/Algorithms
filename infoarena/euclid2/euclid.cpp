#include <bits/stdc++.h>

using namespace std;

ifstream fin("euclid2.in");
ofstream fout("euclid2.out");

const int NMAX = 1e5;

int a, b;

int gcd(int a, int b) {

	return (a == 0) ? b : gcd(b % a, a);
}

int main() {

	int t;
	fin >> t;

	while(t--) {

		fin >> a >> b;
		fout << gcd(a, b) << '\n';
	}

	return 0;
}