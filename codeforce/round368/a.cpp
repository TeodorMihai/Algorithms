#include <bits/stdc++.h>

using namespace std;

const int NMAX = 300;

int n; int m;

char s[NMAX][NMAX];;

int main() {

	int color = 0;

	cin >> n >> m;
	for(int i = 1; i <= n ; ++i)
		for(int j = 1; j <= m ; ++j) {
			cin >> s[i][j];
			if(s[i][j] == 'M' || s[i][j] == 'C' || s[i][j] == 'Y')
				color = 1;
		}

	if(color)
		cout << "#Color\n";
	else 
		cout << "#Black&White\n";

	return 0;
}