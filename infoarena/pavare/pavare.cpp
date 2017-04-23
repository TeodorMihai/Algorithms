#include <bits/stdc++.h>
//pavare maximala cu bucati 2 * 2
using namespace std;

ifstream fin("pavare.in");
ofstream fout("pavare.out");

const int NMAX = 155;
const int MMAX = 15;

int n, m, k, all;
int a[NMAX][MMAX];
int d[NMAX][1 << MMAX];
//d[i][j] = nr de blocuri 2x2 care pot fi amplasate 
//pana la linia i, cu blocurile de multimii j ramase libere

void read() {

	fin >> n >> m >> k;

	for(int i = 1; i <= k; ++i) {

		int x, y; fin >> x >> y;
		x--;
		y--;
		a[x][y] = 1;//bucata buna, nu poate fi pavata
	}
}

void back(int line, int c, int conf, int current, int used) {

	if(c == m) {

		d[line][current] = max(d[line][current], d[line - 1][conf] + used);
		return ;
	}

	int last = (1 << (c - 1));

	if(a[line][c] == 0  &&  (current & last) != 0)  
		if( (conf & last) && (conf & (1 << c)) ) 			
			back(line, c + 1, conf, current - last, used + 1);//le completez
	
	if(a[line][c] == 0)
		back(line, c + 1, conf, current | (1 << c) , used); 
	else 
		back(line, c + 1, conf, current, used);
	//las liber patratelul curent
}

void solve() {

	int line1 = 0;
	all = (1 << m) - 1;

	for(int i = 0 ; i < m; ++i) 
		if(a[0][i] == 0)
			line1 |= (1 << i);

	for(int i = 0 ; i < n ; ++i)
		for(int j = 0 ; j <= all ; ++j)
			d[i][j] = -1;

	d[0][line1] = 0;

	for(int line = 1; line < n; ++line) 
		for(int i = 0 ; i <= all; ++i) {

			if(d[line - 1][i] == -1) continue;
			back(line, 1, i, !a[line][0], 0);
		}
	
	int sol = 0;

	for(int i = 0 ; i <= all ; ++i)
		sol = max(sol, d[n - 1][i]);

	fout << sol << '\n';

}

int main() {

	read(); solve();

	return 0;
}