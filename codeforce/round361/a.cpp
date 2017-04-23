#include <bits/stdc++.h>

using namespace std;

const int NMAX = 22;

char s[NMAX];

int v[NMAX];

void read() {
	int n;
	cin >> n;

	cin >> s;
}

void solve() {

	for(int i = 0 ; i < strlen(s); ++i)
		v[s[i] -'0'] = 1;
	bool ok = false;
	
	bool lung = false; bool lat = false;

	if( (v[1] || v[4] || v[7] ) && (v[3] || v[6] || v[9]))
			lat = true;

	if( (v[1] || v[2] || v[3]) && (v[7] || v[9] || v[8]))
			lung = true;
	
	if(lung && lat && (v[7] || v[9]))
		ok =  true;

	if( (v[1] || v[2] || v[3]) && v[0])
		ok = true;

	if(ok)
		cout << "YES\n";
	else 
		cout << "NO\n";
}

int main() {

	read();

	solve();

	return 0;
}