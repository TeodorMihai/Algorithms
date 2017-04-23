#include <bits/stdc++.h>


using namespace std;

ifstream fin("euclid3.in");
ofstream fout("euclid3.out");

int n;

int gcd(int x, int y) {

	return y == 0 ? x : gcd(y, x % y);
}

int put(int x, int p, int mod) {

	int calc[32];

	int res = 1;

	calc[0] = x;

	for(int i = 1 ; i < 31; ++i)
		calc[i] = (1LL * calc[i - 1] * calc[i - 1] ) % mod;

	for(int i = 0 ; i < 31; ++i)
		if(p & (1 << i)) 
			res = (1LL * res * calc[i]) % mod;
		
	return res;
}




int* solve(int x, int y) {

	int* coef = new int[2]();

	coef[0] = put(x , y - 2, y ); //little ferma theoreme, works only when y is prime, that's the problem
	// with this solution


	coef[1] = (1LL * x * coef[0] - 1) / (-y);

	return coef;

}


int abs(int x) {  return  x > 0 ? x : -x ; }

int main() {

	int x; int y; int c;

	int sgnx;
	int sgny;
	int sgnc;

	int* coef = new int[2]();
	
	fin >> n;


	while(n--) {

		fin >> x >> y >> c;

		sgnx = x / abs(x);
		sgny = y / abs(y);
		sgnc = c / abs(c);
		
		x = abs(x);
		y = abs(y);
		c = abs(c);

		int d = gcd(x, y);



		if(c % d != 0) {
			
			fout << 0 << " " << 0 << '\n';
			
		} else {

			coef = solve(x / d, y / d);
			long long a = 1LL * coef[0] * c / d;
			long long b = 1LL * coef[1] * c / d;

			fout << a * sgnx * sgnc << " " << b * sgny * sgnc << '\n'; 

		}
	}

	return 0;
}