#include <bits/stdc++.h>

using namespace std;

ifstream fin("dinti.in");
ofstream fout("dinti.out");

const int NMAX = 1e6 + 6;
const int MMAX = 1e5 + 5;
const int LMAX = 22;

int n; int m; int l;

bool accept[1<<20];
char s[NMAX];
char q[LMAX];

int bit(int x) { return x & -x; }

void dfs(int node) {

	accept[node] = true;

	int little = 0;

	while(1) {

		int x = node - bit(node - little);
		if(accept[x] == false)
			dfs(x);
		little += bit(node - little);
		if(little == node) break;
	}
}

int main() {

	fin >> n >> m >> l;

	fin >> s + 1;

	int x = 0;
	int mask = (1 << l) - 1;

	for(int i = 1; i <= l - 1 ; ++i)
		x = (x << 1) + (s[i] - '0');

	for(int i = l; i <= n ; ++i) {

		x = (x << 1) + (s[i] - '0');
		dfs( ~x & mask);
	}	

	while(m--) {

		fin >> q;
		x = 0;

		for(int i = 0 ; i < l; ++i)
			x = (x << 1) + q[i] - '0';

		fout << accept[x] << '\n';
	}

	return 0;
}