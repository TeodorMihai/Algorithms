#include <bits/stdc++.h>

using namespace std;


void euclid(int x, int y, int* a, int* b, int* d) {

	if(y == 0) {

		*a = 1;
		*b = 0;
		*d = x;

	} else {

		int a0; int b0;

		euclid(y, x % y, &a0, &b0, d);

		*a = b0;
		*b = 1ll * a0 - 1ll * b0 * (x / y);

	}
}

int invers(int x, int mod) {

	int a; int b; int d;
	
	euclid(x, mod, &a, &b, &d);

	a = a % mod;
	return a < 0 ? a + mod : a;
}

int combinari(int n, int k, int mod) {

	int result = 1;

	for(int i = k + 1; i <= n; ++i)
		result = (1ll * result * i) % mod;

	int imp  = 1;

	for(int i = 2; i <= n - k; ++i)
		imp = (1ll * imp * i) % mod;

	result =  (1ll * result * invers(imp, mod)) % mod;

	return result;
}

int main() {	

	int n; int k;

	cin >> n >> k ;
	cout << combinari(n, k, 997);//last number has to be prime

	return 0;
}