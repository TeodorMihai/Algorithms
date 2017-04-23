#include <bits/stdc++.h>

using namespace std;

ifstream fin("recurenta2.in");
ofstream fout("recurenta2.out");

const int NMAX = 1e9;
const int MOD = 666013;

int x1; int x2; 
int a, b, c;
int n;

int m[7][7]; int v[7];

void constructMatrix() {

	m[1][0] = 1;
	m[0][1] = b; m[1][1] = a; m[2][1] = c;
	m[2][2] = 1;
	m[3][3] = 1; m[4][3] = b; m[5][3] = a; m[6][3] = c;
	m[1][4] = 1; m[5][4] = 1;
	m[0][5] = b; m[1][5] = a; m[2][5] = c; m[4][5] = b; m[5][5] = a; m[6][5] = c;
	m[2][6] = 1; m[6][6] = 1;
}

void inm(int rez[][7], int a[][7], int b[][7]) {


	for(int i = 0 ; i < 7; ++i)
		for(int j = 0 ; j < 7; ++j) {
			rez[i][j] = 0;
			for(int k = 0 ; k < 7; ++k)
				rez[i][j] = (1ll * rez[i][j] + 1ll *  a[i][k] * b[k][j]) % MOD;
		}
}

void putere(int rez[7][7], int p) {

	int put[32][7][7];

	memcpy(put[0], m, sizeof m);

	for(int i = 1; i < 32; ++i)
		inm(put[i], put[i - 1], put[i - 1]);

	memset(rez, 0 , sizeof put[0]);

	int aux[7][7];

	for(int i = 0 ; i < 7; ++i)
		rez[i][i] = 1;

	for(int i = 0 ; i < 32; ++i)
		if( ( 1 << i ) & p ) {

			memcpy(aux, rez, sizeof put[0]);
			inm(rez, aux, put[i]);
		}
}

void inmv(int r[7], int v2[7], int a[7][7]) {

	for(int i = 0 ; i < 7; ++i) {
		r[i] = 0;
		for(int j = 0 ; j < 7; ++j)
			r[i] = (1ll * r[i] + 1ll * v2[j] * a[j][i]) % MOD;
	}
}

int main() {

	fin >> a >> b >> c >> x1 >> x2 >> n;

	constructMatrix();
	v[0] = x1; v[1] = x2; v[2] = 1; v[3] = (x1 + 2 * x2) % MOD;
	v[4] = 3 * x1 % MOD; v[5] = 3 * x2 % MOD; v[6] = 3;//i = 3;

	int rez[7][7];
	putere(rez, n - 2);//m ^ (n - 2)
	int r[7];
	inmv(r, v, rez);

	fout << r[3] << '\n';

	return 0;
}