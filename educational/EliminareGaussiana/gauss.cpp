#include <bits/stdc++.h>

using namespace std;

ifstream fin("gauss.in");
ofstream fout("gauss.out");

const int NMAX = 304;
const double eps = 1e-9;

int n;//nr ecuatii
int m;//nr necunoscute

double a[NMAX][NMAX];

double sol[NMAX];

double modulo(double x) { return x < 0 ? -x : x;}

void read() {

	fin >> n >> m;

	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m + 1; j++) 
			fin >> a[i][j]; 		
}

void gauss() {

	int i = 1; int j = 1;
	//aducere matrice in forma simplificata
	while( i <= n && j <= m) {

		//caut o linie x >= i ai a[x][j] != 0
		int x = i;
		for( ; x <= n; ++x)
			if(modulo(a[x][j]) > eps)
				break;
		if(x == n + 1) { //necunoscuta sol[j] este variabile liber,ii dam valoarea 0
			sol[j] = 0;
			++j;
			continue;
		}
		//interchimb linia x, gasita cu linie curenta, i

		for(int c = 1; c <= m + 1; c++)
			swap(a[i][c], a[x][c]);
		//impart linia i la a[i][j], ca sa fac elementul a[i][j] = 1

		for(int c = j + 1; c <= m + 1; c++)
			a[i][c] /= a[i][j];
		a[i][j] = 1;

		//fac zero sub elementul a[i][j]
		for(int x = i + 1; x <= n ; ++x)  {
			double r = a[x][j]; //cu cat inmultesc toata linia la scadere
			for(int c = j + 1; c <= m + 1; c++)
				a[x][c] -= a[i][c] * r;
			a[x][j] = 0;
		}

		i++; j++;
	}

	//aflare variabile

	for(i = n; i > 0; --i) {

		for(j = 1 ; j <= m + 1; ++j)
			if(modulo(a[i][j]) > eps) {

				if(j == m + 1) { //nu are solutie
					fout << "Imposibil\n";
					exit(0);
				}

				sol[j] = a[i][m + 1];

				for(int k = j + 1; k <= m; ++k)
					sol[j] -= a[i][k] * sol[k];

				//sol[j] /= a[i][j]; nenecesar a[i][j] este deja 1
				break;
			}
	}
}

void print() {

	for(int i = 1; i <= m; ++i)
		fout << fixed << setprecision(10) << sol[i] << '\n';
}

int main() {

	read();
	gauss();
	print();

	return 0;
}