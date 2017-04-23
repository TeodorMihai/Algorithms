#include <bits/stdc++.h>

using namespace std;

ifstream fin("aib.in");
ofstream fout("aib.out");

const int NMAX = 100001;

int N; 

int M;

int v[NMAX]; //v[i] = suma elementelor de la i la i  - (1 << indexului primului bit de 1 la lui i - 1)


void add(int pos, int value) {

	while(pos <= N) { 

		v[pos] += value;

		pos = pos + (pos & -pos);
	}
}





int sum(int pos) { //sum 1...pos


	int s = 0;

	while(pos) {

		s = s + v[pos];

		pos = pos & (pos - 1);
	}

	return s;
}


int findIndex(int s) {

	int pos; int byte;
	
	for( byte = 1 ; byte <= N ; byte <<= 1 );

	for( pos = 0 ; byte ; byte >>= 1)
		if( pos + byte <= N && sum(pos + byte) < s )
			pos += byte;
	
	if(	pos + 1 <= N && sum(pos + 1) == s ) return pos + 1;
	
	return -1;
}

int main() {


	int type; 
	int x; 
	int y;

	fin >> N >> M;

	for(int i = 1 ; i <= N; ++i) {
		fin >> x;
		add(i, x);
	}

	while(M--) {

		fin >> type >> x;
		
		switch(type) {

			case 0: fin >> y; add(x, y); break;
			case 1: fin >> y; fout << sum(y) - sum(x - 1) << '\n';  break;
			case 2:	fout << findIndex(x) << '\n'; break;
		}
	}

	return 0;
}