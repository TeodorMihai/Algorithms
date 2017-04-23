#include <bits/stdc++.h>

using namespace std;

ifstream fin("ssm.in");
ofstream fout("ssm.out");

const int NMAX = 6000009;

int n; int x; 

int smax[NMAX]; int st[NMAX];

int main() {

	fin >> n;

	smax[0] = -0x3f3f3f3f;

	for(int i = 1; i <= n; ++i) {

		fin >> x;

		if( x + smax[i - 1] < x ) {
			st[i] = i;
			smax[i] = x;

		} else {

			smax[i] = smax[i - 1] + x;
			st[i] = st[i - 1];
		}
	}
	int maxi = 1;

	for(int i = 1; i <= n ; ++i)
		if(smax[maxi] < smax[i])
			maxi = i;

	fout << smax[maxi] << ' ' << st[maxi] << ' ' << maxi << '\n'; 
	return 0;
}