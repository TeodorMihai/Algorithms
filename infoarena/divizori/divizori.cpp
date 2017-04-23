#include <bits/stdc++.h>

using namespace std;

ifstream fin("divizori.in");
ofstream fout("divizori.out");

const int FMAX = 12;//nr de factori prim maxim
const int DMAX = 3000;//nr maxim de divizori (aprox n^(1/3))

int n, nrdiv1;
int div1[FMAX][2];//dmax[i][0], div1izorul , dmax[i][1] puterea la care apare
int v[DMAX][FMAX];
int d[FMAX][30];//d[i][j] = i^J


int main() {

	fin >> n;

	for(int i = 2; i * i <= n; ++i) {

		int cntp = 0;
		while(n % i == 0) {
			cntp++;
			n /= i;
		}

		if(cntp) div1[nrdiv1][1] = cntp, div1[nrdiv1++][0] = i;
	}

	if(n > 1) 
		div1[nrdiv1][0] = n, div1[nrdiv1++][1] = 1;	

	for(int i = 0 ; i < nrdiv1; ++i) {
		d[i][0] = 1;
		d[i][1] = div1[i][0];
		for(int j = 2 ; j <= div1[i][1]; ++j)
			d[i][j] = d[i][j - 1] * d[i][1];
	}


	int nr = 0;

	for(int i = 0 ; i <= div1[0][1]; ++i)
		v[nr++][0] = i;

	for(int i = 1; i < nrdiv1; ++i) {

		int nraux = nr;

		for(int j = 1 ; j <= div1[i][1]; ++j) {

			for(int l = 0 ; l < nraux; ++l) {

				if(j % 2 == 0) {
					for(int k = 0 ; k < nrdiv1; ++k) 
						v[nr][k] = v[nr % nraux][k];
				} else {
					for(int k = 0 ; k < nrdiv1; ++k)
						v[nr][k] = v[nraux - (nr % nraux) - 1][k];
				}

				v[nr][i] = j;
				nr++;
			}
		}
	}

	int div = 1;

	fout << nr << '\n';

	for(int i = 0; i < nr; ++i) {

		div = 1;

		for(int k = 0 ; k < nrdiv1; ++k)
			div *= d[k][v[i][k]];

		fout << div << ' ';
	}

	return 0;
}