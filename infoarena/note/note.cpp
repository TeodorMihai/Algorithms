#include <bits/stdc++.h>

using namespace std;

#define DELETE 1
#define INSERT 1
#define SUBSTITUTE 1

ifstream fin("note.in");
ofstream fout("note.out");

const int VMAX = (1<<9);
const int NMAX = (1<<10);

int d[NMAX + 1][NMAX + 1];

int a[VMAX + 1][NMAX + 1];
int b[NMAX + 1];

//d[i][j] = costul minim de a broda solfegiul [1...j] la toate partiturile de lungime [1...i]
int v; int n; int m;

void read() {

	fin >> v >> n;

	for(int i = 1; i <= v; ++i) 
		for(int j = 1; j <= n; ++j)
			fin >> a[i][j];

	fin >> m;

	for(int i = 1; i <= m; ++i)
		fin >> b[i];
}

void solve() {

	d[0][0] = 0;

	for(int i = 0 ; i <= m ; ++i)
		d[0][i] = i; //le stergem e toate

	for(int i = 1; i <= n; ++i)
		d[i][0] = i; //le inseram pe toate

	int cost = 0;

	//putem modifica doar b => 
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j) {

			cost = SUBSTITUTE;//costul de substituire
			
			for(int k = 1; k <= v; ++k)
				if(b[j] == a[k][i]) {
					cost = 0;
					break;
				}

			d[i][j] = d[i - 1][j - 1] + cost;
			d[i][j] = min(d[i][j] , d[i - 1][j] + DELETE); //stergem j
			d[i][j] = min(d[i][j], d[i][j - 1] + INSERT); //inseram ce trebuie pe pozitia j
		}

	fout << d[n][m] << '\n'; 
}

int main() {

	read();

	solve();

	return 0;
}