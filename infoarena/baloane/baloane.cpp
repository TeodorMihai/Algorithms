#include <bits/stdc++.h>

using namespace std;

ifstream fin("baloane.in");
ofstream fout("baloane.out");

const int NMAX = 55;
const int MMAX = 15;

int n, m, t;
int b[MMAX];
double p[NMAX][MMAX];
double d[NMAX][NMAX];
//d[i][j] = probabilitatea ca din i echipe j sa o rezolve corect
double ps[MMAX], ans = 1.0;

int main() {

	fin >> t;

	while(t--) {

		ans = 1;

		fin >> n >> m;

		for(int i = 1; i <= m ; ++i)
			fin >> b[i];

		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m ; ++j)
				fin >> p[i][j], p[i][j] *= 0.01;

		for(int i = 1; i <= m ; ++i) {

			d[0][0] = 1;
			for(int j = 1; j <= n; ++j)
				d[0][j] = 0;

			for(int j = 1; j <= n; ++j) 
				for(int k = 0; k <= j; ++k) {

					d[j][k] = 0;

					if(k >= 1)
						d[j][k] = d[j - 1][k - 1] * p[j][i];
					
					d[j][k] += d[j - 1][k] * (1 - p[j][i]);
				}	

			ps[i] = 0;
			
			for(int j = 0; j <= b[i]; ++j)
				ps[i] += d[n][j];
			ans *= ps[i];
		}

		ans *= 100;
		fout << fixed << setprecision(4) << ans << '\n';

	}

	return 0;
}