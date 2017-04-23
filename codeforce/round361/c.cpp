#include <bits/stdc++.h>

using namespace std;

#define in64 long long

in64 NMAX = 1ll * (1e16 + 2);


in64 m; in64 n;

in64 maxi;


void read() {

	cin >> m;


}


in64 sum(in64 nr) {

	in64 s = 0;

	for(int i = 2; i <= maxi; ++i) {
		in64 res = nr / (1ll * i * i * i);
		
		if(res == 0) return s;

		s += res;	
	}

	return s;
}

void solve() {

	for(maxi = 1 ; maxi * maxi * maxi  <= m * 8; ++maxi);


	in64 step ; in64 pos = 0;

	for(step = 1; step <= NMAX; step <<= 1);

	for(pos = 0 ; step ; step >>= 1)
		if(step + pos < NMAX && sum(pos + step) < m)
			pos += step;
	if(sum(pos + 1) == m)
		cout << pos + 1 << '\n'; 
	else 
		cout << -1 << '\n';
}

int main() {

	read(); solve();

	return 0;
}
