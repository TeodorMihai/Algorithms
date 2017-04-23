#include <bits/stdc++.h>

using namespace std;

ifstream fin("buget.in");
ofstream fout("buget.out");


#define ll long long
const long long NMAX = 100001;
const long long MAJ = 1000000000000000;

ll s, n, v[NMAX], sum[NMAX];


bool cmp(ll x, ll y) {

	return x < y;
}


int bs2(ll x) {

	int step = 1; int pos = 1;

	for(; step <= n ; step <<= 1);

	for(;step ; step >>= 1)
		if(pos + step <= n && v[pos + step] <= x)
			pos +=step;
	return pos;
}
ll cost(ll x) {

	int index = bs2(x);

	ll total = sum[index];

	total += (n - index) * x;
	return total;
}

ll bs() {

	ll step = 1; ll pos = 0;

	for( ; step <= MAJ; step *= 2);

	for(; step ;  step >>= 1)
		if(pos + step <= MAJ  && cost(pos + step) <= s)
			pos += step;
	
	return pos;

}

int main() {

	fin >> n >> s ;

	for(int i = 1; i <= n; ++i)
		fin >> v[i];

	sort(v + 1, v + 1 + n, cmp);


	for(int i = 1; i <= n ; ++i)
		sum[i] = sum[i- 1] + v[i];

	fout << bs();

	return 0;
}