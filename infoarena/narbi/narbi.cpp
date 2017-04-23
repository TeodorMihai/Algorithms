#include <bits/stdc++.h>

using namespace std;

ifstream fin("narbi.in");
ofstream fout("narbi.out");

typedef int in64;

const int NMAX = 16e6 + 5;
const int MOD = 71;

int n; int k; in64 x;

int h[MOD];


int countBits(in64 x, int nr) {
	//nr = nr de biti pentru x
	//obtinem nr de biti pentru x + 1
	in64 neg = ~x;
	return nr - h[(neg & -neg) % MOD] + 1;
}

int main() {

	fin >> n >> k >> x;

	for(int i = 0 ; i < 33; ++i)
		h[(1ll << i) % 71 ] = i;
	
	in64 r = 0;
	in64 pre = 0;
	
	for(int i = 0; i < x; ++i) {
		pre = countBits(i, pre);
		//pre = __builtin_popcount(i);
		r += pre;
	}

	if(k == n) 
		fout << r << '\n', --k;

	in64 mask = (1 << 4) - 1;

	for(int i = 2; i <= n ; ++i) {

		in64 oldX = x;
		in64 newX = x + (r & mask) + 1;

		for(in64 j = oldX ; j < newX; ++j) {
			//pre = __builtin_popcount(j);
			pre = countBits(j , pre);
			r += pre;
		}

		if(n - i + 1 <= k)
			fout << r << '\n';

		x = newX;
	}

	return 0;
}