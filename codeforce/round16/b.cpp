#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3e5 + 5;
int n;

int v[NMAX];

int main() {


	cin >> n;

	for(int i = 1; i <= n ; ++i) {
		cin >> v[i];
	}

	sort(v + 1, v + 1 + n);

	if(n % 2 == 1)
		cout << v[n / 2 + 1] << '\n';
	else 
		cout << v[n / 2] << '\n';

	return 0;
}