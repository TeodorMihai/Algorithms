#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5 + 5;

int n;

int v[NMAX];


int can = 1;

int main() {

	cin >> n;
	
	for(int i = 1; i <= n ; ++i)
		cin >> v[i];
	for(int i = 1; i <= n ; ++i) {

		if(v[i] % 2 == 1) {
			
			v[i]--;

			v[i + 1]--;

			if(v[i] < 0) can = 0;

			if(v[i + 1] < 0) can = 0;
			
			if(i + 1 > n) can = 0;
		}
	}

	if(can)
		cout << "YES\n";
	else 
		cout << "NO\n";
	return 0;
}