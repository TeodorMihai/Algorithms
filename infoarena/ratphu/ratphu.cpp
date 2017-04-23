#include <bits/stdc++.h>

using namespace std;

ifstream fin("ratphu.in");
ofstream fout("ratphu.out");

const int NMAX = 19;
const int PMAX = 21;

long long d[1 << 18 + 2][PMAX];
//d[i][j] = nr de permutari posibile daca se folosesc cifrele retinute in i
//cu restul j la impartirea cu p

int n; int p;
char s[NMAX];


int mod(int x) {

	while(x >= p)
		x -= p;
	return x;
}

int main() {

	fin >> s >> p;

	n = strlen(s);
	int lim = (1 << n) ;
	d[0][0] = 1;

	for(int i = 0 ; i < lim; ++i) 
		for(int j = 0 ; j < p; ++j) {
			
			if(d[i][j] == 0) continue;
			
			for(int k = 0 ; k < n; ++k) {
				if( (1<<k) & i ) continue; //a k-a cifra fface deja parte din configuratie
				d[i + (1<<k)][mod(j * 10 + (s[k] - '0'))] += d[i][j];
			}

		}

	fout << d[lim - 1][0] << '\n'; 

	return 0;
}