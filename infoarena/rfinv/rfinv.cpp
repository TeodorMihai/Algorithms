#include <bits/stdc++.h>

using namespace std;

ifstream fin("rfinv.in");
ofstream fout("rfinv.out");

const int NMAX = 52;

int n; int t; int m;

int a[NMAX][NMAX];
bool b[NMAX][NMAX];

void read() {

	fin >> n >> m;

	for(int i = 1; i <= m ; ++i) {
		int x; int y;
		fin >> x >> y;
		b[x][y] = true;
		b[y][x] = true;
	}

	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n ; ++j)
			fin >> a[i][j];
}

void solve() {

	bool solution = true;

	for(int i = 1; i <= n ; ++i)
		for(int j = 1; j <= n ; ++j) {

			if(i == j) continue;
			
			int mini = 0x3f3f3f3f;

			for(int k = 1; k <= n ; ++k)
				if(mini > a[i][k] + a[k][j] && k != j && k != i)
					mini =  a[i][k] + a[k][j];

			if(mini < a[i][j])
				solution = false;

			if(mini > a[i][j] && b[i][j] == false)
				solution = false;
		}

	if(solution == true)
		fout << "DA\n";
	else 
		fout << "NU\n";
}

void clean() {

	for(int i = 1; i <= n ;++i)
		memset(b[i], 0, sizeof(b[i]));
}

int main() {

	fin >> t;

	while(t--) {

		read();
		solve();
		clean();
	}

	return 0;
}