//construiesc probabilitatea finala astfel incat sa se potriveasca cu restul
//probabilitatilor: dist medie de la i la N dist[i] = (dist[j] + cost[j][i]) * prob(i, j)
//unde prob(i, j) este porbabilitatea de a merge in j daca sunt in i = 1/gr[i]
//pentru fiecare vecin j
//pentru fiecare nod i scriu aceste ecuatii => un sistem
#include <bits/stdc++.h>

using namespace std;

ifstream fin("tunel.in");
ofstream fout("tunel.out");

const int NMAX = 260;
const int MMAX = 1e5 + 5;
const double eps = 1e-8;

int n; int m;

double degree[NMAX];
double a[NMAX][NMAX];//n * n sistem

double cost[MMAX];
int x[MMAX];
int y[MMAX];

double sol[NMAX];

double b[NMAX];

void read() {

	fin >> n >> m;

	for(int i = 1; i <= m ; ++i) {
		fin >> x[i] >> y[i] >> cost[i];
		degree[x[i]]++;
		degree[y[i]]++;
	}
}


void gauss() {

	int i = 1; int j = 1;
	
	while(i <= n && j <= n) {

		int x = i;
		for(; x <= n && fabs(a[x][j]) < eps; ++x);

		if(x == n + 1) { //variabila libera
			sol[j] = 0;
			j++;
			continue;
		}

		for(int c = 1; c <= n ; ++c)
			swap(a[x][c], a[i][c]);
		swap(b[x], b[i]);

		for(int c = j + 1; c <= n; c++)
			a[i][c] /= a[i][j];
		b[i] /= a[i][j];
		
		a[i][j] = 1.0;

		//a[x][j] == 1
		for(x = i + 1; x <= n ; ++x) {
			double inm = a[x][j];
			for(int c = 1; c <= n ; ++c)
				a[x][c] -= inm * a[i][c];
			b[x] -= inm * b[i];
			a[x][j] = 0;
		}

		i++; j++;
	}

	for(i = n ; i > 0 ; --i) {

		for(j = 1; j <= n + 1 && fabs(a[i][j]) < eps ; ++j);

		if(j == n + 1) {
			cout << "Nasol\n";
			exit(0);
		} 

		sol[j] = b[i];

		for(int c = j + 1; c <= n; ++c)
			sol[j] -= a[i][c] * sol[c];
	}
}

void solve() {

	for(int i = 1; i <= n ; ++i)
		a[i][i] = -1.0;

	for(int i = 1; i <= m ; ++i) {
		//x[i] -> y[i] -> ... -> n
		a[x[i]][y[i]] += (double) 1.0 / degree[x[i]];
		//y[i] -> x[i] -> ... -> n
		
		a[y[i]][x[i]] += (double) 1.0 / degree[y[i]];

		b[x[i]] -= 1.0 * cost[i] / degree[x[i]];
		b[y[i]] -= 1.0 * cost[i] / degree[y[i]];
	}
	n--;
	gauss();
	fout << fixed << setprecision(7) ;
	fout << sol[1] << '\n';

}

int main() {

	read();

	solve();

	return 0;
}