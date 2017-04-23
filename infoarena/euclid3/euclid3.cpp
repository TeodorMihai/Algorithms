#include <bits/stdc++.h>

using namespace std;

ifstream fin("euclid3.in");
ofstream fout("euclid3.out");

int a, b, c;
//x * a + y * b = c, gasiti (x, y)
// 2 5
// 5 7

int solve(int& x, int& y, int a, int b) {

	if(a == 0) {
		x = 0;
		y = 1;
		return b;	
	} else {

		int x0, y0;
		int gcd = solve(x0, y0, b % a, a);
		y = x0;
		x =  (1ll * gcd - 1ll * y * b) / a;
		return gcd;
	}
}

int main() {

	int t; fin >> t;

	while(t--) {

		fin >> a >> b >> c;

		int x, y;
		int gcd = solve(x, y, a, b);
		if(c % gcd != 0) {
			fout << 0 << ' ' << 0 << '\n';
		} else 
			fout << 1ll * x * (c / gcd) << ' ' << 1ll * y * (c / gcd) << '\n';

	}
	return 0;	
}