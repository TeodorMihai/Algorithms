#include <bits/stdc++.h>

using namespace std;

const int NMAX = 5005;
int v[NMAX];
int sum[NMAX];
int n;

int main() {

	cin >> n;

	for(int i = 2; i <= n ; ++i) {
		cout << "? " << 1 << ' ' << i << '\n';
		fflush(stdout);
		cin >> sum[i];
	}

	cout << "? " << 2 << ' ' << 3 << '\n';
	fflush(stdout);
	//fflush(stdin);
	cin >> sum[1];

	v[1] = (sum[2] + sum[3] - sum[1]) / 2;

	for(int i = 2; i <= n ; ++i)
		v[i] = sum[i] - v[1];

	cout << "! ";

	for(int i = 1; i <= n ; ++i)
		cout << v[i] << ' ';
	cout << '\n';
	fflush(stdout);

	return 0;
}