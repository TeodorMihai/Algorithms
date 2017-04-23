#include <bits/stdc++.h>


using namespace std;

ifstream fin("euclid3.in");
ofstream fout("euclid3.out");

int n;

int euclid(int a, int b, int* x, int* y) {

	if(b == 0) {
		
		*x = 1;
		*y = 0;
		return a;

	} else {

		int y0;
		int x0;

		int d = euclid(b, a % b, &x0, &y0);
		
		int c = a / b;

		*x = y0;
		*y = x0 - c * y0;
		return d;
	}
}


int main() {

	int a; int b; int c;

	int x; int y; int d;

	fin >> n;

	while(n--) {

		fin >> a >> b >> c;

		d = euclid(a, b, &x, &y);

		if(c % d != 0)
			fout << 0 << " " << 0 << '\n';
		else 
			fout << (int)(1ll * x * c / d) << " "<< (int)(1ll * y * c / d) << '\n'; 
		
	}

	return 0;
}