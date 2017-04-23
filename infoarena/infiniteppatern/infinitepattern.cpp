#include <bits/stdc++.h>


using namespace std;


ifstream fin("infintepatternmatching.in");
ofstream fout("infintepatternmatching.out");

#define ll long long


char s[60];

int n;


ll constructNumber(char* s,int st, int dr) {


	ll val = 0;

	for(int i = st ; i < dr ; ++i) {

		val = s[i] -'0' + (val << 1);
	}

	return val;
}

int check(ll x, ll y, int ind, int k) {

	ll mask = (1<<ind) - 1;

	int ok = 0;
	if( (x >> (k - ind)) & mask == y & mask)
		ok = 1;

	return ok;

}


ll find(ll x, ll r) {

	ll biti = 1;
	ll total = 0;

	for(ll i = 1 ; i <= x; ++i ) {

		if(i  ==  (1 << biti))
			biti++;
		total = total + biti;
	}

	return total + r;
}

int main() {


	ll mini = (1 << 60);

	fin >> s;

	cout << s << '\n'; 

	n = strlen(s);

	ll nr = constructNumber(s,0,  n);

	ll rest;

	for(int i = 0 ; i < n + 1; ++i ) {

		// de la i incolo inclusiv e al doilea numar

		ll x = constructNumber(s, 0, i);
		ll y = constructNumber(s, i , n);


		//din cifre comune ai
		for(int j = 0  ; j < i ; ++j) {
			cout << x << '\n';
			if(check( x, nr, j, i)) {
				
				ll p = y << (i - j) + x;

				if(p < mini) {
					rest = n - i;
					mini = p;
				}

			}
		}


	}

	fout << find(mini, rest);

	return 0;
}