#include <bits/stdc++.h>

using namespace std;

ifstream fin("nkbiti.in");
ofstream fout("nkbiti.out");

typedef int in64;

const int NMAX = 1e9;
const int KMAX = 43;
const in64 MOD = 666777;

int n; int k;

in64 x[KMAX]; //x[i + 1] = cate siruri se pot forma atfel incat ulimii i biti sunt 0

in64 a[KMAX][KMAX];
in64 put[32][KMAX][KMAX];

void formMatrix() {

	for(int i = 1; i <= k; ++i)
		a[1][i] = 1;

	for(int i = 2; i <= k; ++i)
		a[i][i - 1] = 1;
}

//rez = a * b
void inm(in64 rez[][KMAX], in64 a[][KMAX], in64 b[][KMAX]) {

	memset(rez, 0, sizeof put[0]);

	for(int i = 1; i <= k; ++i)
		for(int j = 1; j <= k; j++)
			for(int l = 1; l <= k ; ++l)
				rez[i][j] = (1ll * rez[i][j] + 1ll * a[i][l] * b[l][j] ) % MOD;
}

//rez = a * v
void inmVector(in64 rez[KMAX], in64 a[][KMAX], in64 v[KMAX]) {

	memset(rez, 0, sizeof put[0][0]);

	for(int i = 1; i <= k; ++i)
		for(int j = 1; j <= k ; ++j)
			rez[i] = (1ll * rez[i] + 1ll * a[i][j] * v[j]) % MOD;
}


void power(in64 rez[][KMAX], in64 a[][KMAX], in64 p) {

	//put[i] = a ^ (2 ^ i)
	for(int i = 1; i <= k ; ++i)
		rez[i][i] = 1;

	//print(a);
	memcpy(put[0], a, sizeof put[0]);
	//	print(put[0]);

	for(int i = 1; i < 32; ++i)
		inm(put[i], put[i - 1], put[i - 1]);

	in64 aux[KMAX][KMAX];

	for(int i = 0 ; i < 32; ++i)
		if( (1 << i) & p) {

			memset(aux, 0 , sizeof aux );
			inm(aux, rez, put[i]);
			memcpy(rez, aux, sizeof aux);
		}
}


int main() {

	fin >> n >> k;

	if(n <= k) {
		fout << (1ll << n);
		exit(0);
	}

	for(int i = 1; i <= k + 1; ++i)
		x[i] = (1ll << (k + 1 - i)) % MOD;

	++k;
	formMatrix();

	in64 trans[KMAX][KMAX];
	//k - 1 + n - k + 2 = n + 1 biti

	power(trans, a, n - k + 1);

	in64 ans[KMAX];
	inmVector(ans, trans, x);

	fout << ans[1] << '\n';
	return 0;
}