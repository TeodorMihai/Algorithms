#include <bits/stdc++.h>

using namespace std;


const int NMAX = 222;

int a[360][360];
char s[NMAX];

int main() {

	cin >> s;
	int n = strlen(s);

	for(int i = 'a' ; i <= 'z'; ++i)
		for(int j = 'a' ; j <= 'z'; ++j) {

			int dif = abs(i - j);

			a[i][j] = min(dif, 26 - dif);
		}

	char let = 'a';
	int ans = 0;

	for(int i = 0 ; i < n ; ++i) {
		ans += a[let][s[i]];
		let = s[i];
	}

	cout << ans << '\n';

	return 0;
}