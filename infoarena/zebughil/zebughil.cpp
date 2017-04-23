#include <bits/stdc++.h>

using namespace std;

ifstream fin("zebughil.in");
ofstream fout("zebughil.out");

const int NMAX = 17;

int n; int v[NMAX]; int g;

int d[1<<NMAX][NMAX + 1];
//d[i][j] = cat mai pot sa bag in ultimul camion (maxim)
//daca transporat blocurile cu bitii 1 din configuratia lui i 
//si folosind j camioane

void solve(int n, int g) {

	d[0][0] = 0;

	int all = (1 << n) - 1;

	for(int i = 1; i <= all; ++i)
		for(int c = 0; c <= n ; ++c)
			d[i][c] = -1;

	for(int i = 0; i <= all; ++i) {

		for(int j = 0; j < n; ++j) {
			
			if(i & (1 << j)) continue;

			for(int c = 0; c <= n ; ++c){
				if(d[i][c] != -1) {	 
					d[i + (1 << j)][c] = max(d[i + (1 << j)][c], d[i][c] - v[j]);
					if(c + 1 <= n)
						d[i + (1 << j)][c + 1] = max(d[i + (1 << j)][c + 1], g - v[j]);
				}
			}
		}
	}

	int ans = 0x3f3f3f3f;

	for(int c = 1; c <= n; ++c)
		if(d[all][c] != -1) {
			ans = c; break ;
		}
		
	fout << ans << '\n';

}

int main() {

	//elementele nu au o odine anume!! daca vreau o anumita configuratie 
	//o pot obtine cu ultimul element oricare
	//de unde vine optimizarea fata de n ^ n ? 
	for(int i = 1; i <= 3; ++i) {

		fin >> n >> g;
		for(int j = 0; j < n ; ++j)
			fin >> v[j];
		solve(n, g);
	}

	return 0;
}