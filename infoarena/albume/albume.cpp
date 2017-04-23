#include <bits/stdc++.h>

using namespace std;

ifstream fin("albume.in");
ofstream fout("albume.out");

const int NMAX = 1002;

double c, k, q;

int main() {

	fin >> c >> k >> q;
	double p = 1;
	for(double  i = 1; i <= k ; ++i)
		p *= (k * c - q - k + i) / (k * c - k + i);
	fout << fixed << setprecision(8) << c * (1 - p) << '\n';
	return 0;
}