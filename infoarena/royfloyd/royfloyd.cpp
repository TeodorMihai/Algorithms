#include <bits/stdc++.h>

using namespace std;

ifstream fin("royfloyd.in");
ofstream fout("royfloyd.out");

const int NMAX = 102;
const int INF = 0x3f3f3f3f;
int n;
int a[NMAX][NMAX];

int main() {

	fin >> n;

	for(int i = 1; i <= n ; ++i)
		for(int j = 1; j <= n ; ++j) {
			fin >> a[i][j];
			if(a[i][j] == 0)
				a[i][j] = INF;
		}

	for(int k = 1; k <= n ; ++k) //folosind doar primele k noduri
		for(int i = 1; i <= n ; ++i)
			for(int j = 1; j <= n ; ++j) {

				if(i != j && a[i][j] > a[i][k] + a[k][j])
					a[i][j] = a[i][k] + a[k][j];
			}

	for(int i = 1; i <= n ; ++i) {
		for(int j = 1; j <= n ; ++j)
			if(a[i][j] == INF)
				fout << 0 << ' ';
			else 
				fout << a[i][j] << ' ';
		fout << '\n';
	}


	return 0;
}