#include <bits/stdc++.h>

using namespace std;

const int NMAX = 55;

int n;

int a[NMAX][NMAX];

int imp = 1;
int par = 2;

int main() {

	cin >> n;

	for(int j = 1 ; j <= n / 2; ++j) {


		for(int i = 1; i <= n / 2; ++i) {

			if(i <= j) 
				a[i][j] = 2;
			else 
				a[i][j] = 1;

			a[n - i + 1][j] = a[i][j];

			a[i][n - j + 1] = a[i][j];
			a[n - i + 1][n - j + 1] = a[n - i + 1][j];
		}
	}

	

	for(int i = 1; i <= n; ++i)
		a[i][n / 2 + 1] = 1;

	for(int j = 1; j <= n; ++j)
		a[n / 2 + 1][j] = 1;

	for(int i = 1; i <= n ; ++i) {

		for(int j = 1; j <= n ; ++j)
			if(a[i][j] == 1) {
				cout << imp << ' ';
				imp += 2;
			} else {

				cout << par << ' ';
				par += 2;
			}

		cout << '\n';
	}

	return 0;
}