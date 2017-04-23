#include <bits/stdc++.h>

using namespace std;

ifstream fin("cmlsc.in");
ofstream fout("cmlsc.out");

const int NMAX = (1 << 10) + 10;

int n, m;
int v1[NMAX], v2[NMAX];
int a[NMAX][NMAX];
//a[i][j] = cmlsc cu primele i elemente din v1 si j din v2


void print(int x, int y) {

	if(x == 0 || y == 0) return ;

	if(a[x][y] == a[x - 1][y - 1] + 1 && v1[x] == v2[y]) {
		print(x - 1, y - 1);
		fout << v1[x] << ' ';
	} else if(a[x][y] == a[x][y - 1])
		print(x, y - 1);
	else print(x - 1, y);
}

int main() {

	fin >> n >> m;
	
	for(int i = 1; i <= n ; ++i)
		fin >> v1[i];
	
	for(int i = 1; i <= m ; ++i)
		fin >> v2[i];

	for(int i = 1; i <= n ; ++i)
		for(int j = 1; j <= m ; ++j) {

			if(v1[i] == v2[j]) 
				a[i][j] = a[i - 1][j - 1] + 1;

			a[i][j] = max(a[i][j], a[i - 1][j]);
			a[i][j] = max(a[i][j], a[i][j - 1]);
		}

	fout << a[n][m] << '\n';
	print(n, m);

	return 0;
}