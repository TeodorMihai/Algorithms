#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1009;

int n; int m;

char s[NMAX][NMAX];

int main() {

	cin >> n >> m;

	for(int i = 1; i <= n; ++i)
		cin >> s[i] + 1;

	int x = 0;
	int y = 0;

	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j) {

			bool another =false;
			if(s[i][j] == '*') {

				for(int c = 1 ; c <= m; ++c)
					if(s[i][c] == '*')
						another = true;
				if(another)
					y = j;
				else 
					x = i;
				i = n + 1;
				break;
			}
		}

	if(x == 0) {

		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
				if(s[i][j] == '*' && j != y) {
					x = i;
					break;
				}
	}


	if(y == 0) {

		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
				if(s[i][j] == '*' && i != x) {
					y = j;
					break;
				}
	}

	bool can = true;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			if(s[i][j] == '*' && i != x && j != y )
				can = false;
	if(x == 0)
		x = 1;
	if(y == 0)
		y = 1;
	
	if(can)
		cout << "YES\n" << x << ' ' << y << '\n';
	else 
		cout << "NO\n";


	return 0;
}