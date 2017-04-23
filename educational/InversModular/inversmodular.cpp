#include <bits/stdc++.h>

using namespace std;

ifstream fin("inversmodular.in");
ofstream fout("inversmodular.out");

int a;
int n;


void euclid(int x, int y, int* a, int* b, int* d) {

	if(y == 0) {

		*a = 1;
		*b = 0;
		*d = x; //1 in our case
	} else {

		int a0; int b0;

		euclid(y, x % y, &a0, &b0, d);

		*a = b0;
		*b = 1ll * a0 - 1ll * b0 * (x / y);
	}
}

int findInvers(int a, int n) {

	int x; int y; int d;

	
	euclid(a, n, &x, &y, &d);
	//a * x + n * y = 1 => a*x = 1 mod n => x invers modular a lui a
	x = x % n;
	
	if(x < 0) x += n;

	return x;
}

int main() {


	//a * x + y * b = 1, daca x si y sunt prime intre ele

	//mereu adevarat pentru ca a * x + b * y = cmmdc(x, y) = 1
	// x = a 
	// y = n

	fin >> a >> n ;

	fout << findInvers(a, n) << '\n';

	return 0;
}