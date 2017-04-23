#include <bits/stdc++.h>

/*O(3^n) generezi submultimi (de noduri la grafuri, cu muchiile doar in graful cu nodurile
respective, apoi o calcuezi cu o formula dupa partitionarea multimii respective  in 2 
2 submultimi deja calculate
informatie la fel greu de calculat aka echivalenta : nr de grafuri partiale (fara muchii) conexe 
 <=> nr de grafuri partiale neconexe*/

using namespace std;

ifstream fin("ndap.in");
ofstream fout("ndap.out");

const int NMAX = 15;
const int MOD = 30103;

int n, m;
vector<int> g[NMAX];
int d[1<<NMAX];//d[i] = nr de comp conexe ale subgrafului i
int e[1<<NMAX];//e[i] = nr de muchii ale subgrafului i
int put[NMAX * NMAX + 6];//put[i] = 2 ^ i mod MOD

void read() {

	fin >> n >> m;

	for(int i = 1; i <= m; ++i) {
		int x, y; fin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
}

void solve() {

	put[0] = 1;
	for(int i = 1; i <= m; ++i)
		put[i] = (put[i - 1] * 2) % MOD;

	int all = (1 << n) - 1;

	for(int i = 1 ; i <= all; ++i) {

		int node;

		for(int j = 0 ; j < n ; ++j)
			if( (1 << j) & i) {
				node = j;
				break;
			}

		e[i] = e[i xor (1 << node)];

		for(int x : g[node])
			if( (1 << x) & i)
				e[i]++;
	}

	for(int i = 0 ; i < n; ++i)
		d[1 << i] = 1;

	for(int i = 1 ; i <= all; ++i) {

		if(d[i] == 1) continue;
		//calculam nr de comp neconexe al subgrafului i
		//luam toate subgrafului lui i care contin nodul x (lsb de 1) al lui
		int x = i & -i;
		int neconex = 0;
		int ci = ~i;

		for(int j = 1 ; j < i; j = (j + 1 + ci)&~ci ) {

			if( (x & j) == 0) continue ;
			if( (j | i) != i) continue ;
			int complement = i xor j;
			neconex = (neconex + d[j] * put[e[complement]]) % MOD;
		}

		d[i] = put[e[i]] - neconex;
		if(d[i] < 0)
			d[i] += MOD;
	}

	fout << d[all] << '\n';
}

int main() {

	read(); solve();
	return 0;
}