#include <bits/stdc++.h>

using namespace std;

ifstream fin("permutari.in");
ofstream fout("permutari.out");

const int NMAX = 9;

int n;
int perm[NMAX];
int used[NMAX];


void back(int k) {

	if(k == n + 1) {

		for(int i = 1; i <= n ; ++i)
			fout << perm[i] << ' ';
		fout << '\n';

	} else {

		for(int i = 1; i <= n ; ++i)
			if(used[i] == 0) {
				perm[k] = i;
				used[i] = 1;
				back(k + 1);
				used[i] = 0;
			}
	}
}

int main() {

	fin >> n ;
	back(1);
	return 0;
}