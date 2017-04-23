#include <bits/stdc++.h>

using namespace std;

ifstream fin("jap2.in");
ofstream fout("jap2.out");

typedef long long in64;

const int PMAX = 1e5 + 7;
const int QMAX = 1e5 + 5;
const in64 AMAX = 1e18;

int p; int q;

int fact[PMAX];
int pu[64];
vector<int> bits;

in64 order(in64 x, in64 a) {

	in64 cnt = 0;

	for(in64 i = a; x / i != 0; i *= a)
		cnt += x / i;

	return cnt;
}


int putere(int x) {

	int put[64];
	//put[i] = x ^ ( 2 ^ i)
	put[0] = x;
	for(int i = 1; i < 32; ++i)
		put[i] = 1ll * put[i - 1] * put[i - 1] % p;
	
	int rez = 1;

	for(int x : bits)
		rez = 1ll * rez * put[x] % p;

	return rez;
}

int putf(in64 po) {

	int rez = 1;

	for(int i = 0 ; i < 64; ++i)
		if(po & (1 << i))
			rez = 1ll * rez * pu[i] % p;

	return rez;
}

int factorial(in64 a) {

	if(a == 0)
		return 1;
	
	in64 div = a / p;

	return 1ll * putf(div) * fact[a % p] * factorial(div) % p;
}

int comb(in64 a, in64 b) {

	//a! / ( b!  *  (a - b)!)

	in64 af = order(a, p);
	in64 bf = order(b, p);
	in64 abf = order(a - b, p);

	if(af > bf + abf) return 0;

	return 1ll * factorial(a) * putere(factorial(b)) 
		* putere(factorial(a - b)) % p;
}

int main() {

	fin >> p >> q;

	fact[0] = 1;
	for(int i = 1; i < p ; ++i)
		fact[i] = (1ll * fact[i - 1] * i) % p;

	pu[0] = fact[p - 1];
	for(int i = 1; i < 64; ++i)
		pu[i] = 1ll * pu[i - 1] * pu[i - 1] % p;

	for(int i = 0 ; i < 32; ++i)
		if( (1 << i) & (p - 2))
			bits.push_back(i);

	while(q--) {

		in64 a; in64 b;
		fin >> a >> b;
		fout << comb(a, b) << '\n';
	}

	return 0;
}