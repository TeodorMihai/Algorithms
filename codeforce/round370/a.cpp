#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5 + 5;

int n;

int a[NMAX], b[NMAX];

int main() {	


	cin >> n ;

	for(int i = 1; i <= n; ++i)
		cin >> a[i];

	b[n] = a[n];

	for(int i = n - 1; i > 0 ; --i) 
		b[i] = a[i] + a[i + 1];

	for(int i = 1; i <= n; ++i)
		cout << b[i] << ' ';
	cout << '\n';
	
	return 0;
}