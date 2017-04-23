#include <bits/stdc++.h>

using namespace std;

ifstream fin("euclid3.in");
ofstream fout("euclid3.out");

const int TMAX = 102;


int euclid(int a, int b, int &x, int &y) {

	if(b == 0) {
		x = 1;
		y = 0;
		return a;//cmmdc
	}  else {
			
		int x0, y0;
		int d = euclid(b , a % b, x0, y0);
		//ax + by = d vrem x si y
		//bx0 + (a % b)y0 = d stim 
		int c = a / b;
		x = y0;
		y = (1ll * d - 1ll * a * x) / b;

		return d;
	}
}


int main() {

	int a; int b; int c;
	
	int t;

	fin >> t;

	while(t--) {

		fin >> a >> b >> c;

		//a * x + b * y = c determina x si y
		int x, y;
		int d = euclid(a, b, x, y);
		if(c % d == 0)
			fout << 1ll* x * c / d << ' ' << 1ll * y * c / d << '\n';
		else 
		    fout << 0 << ' ' << 0 << '\n';
	}

	return 0;
}