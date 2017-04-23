#include <bits/stdc++.h>

using namespace std;

ifstream fin("numerologie.in");
ofstream fout("numerologie.out");

const int NMAX = 1255;
const int KMAX = 11;

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
int n, m;

int v[NMAX];
int cost[NMAX];
vector<int> div1[NMAX];
int indexp[33];
int taken[NMAX];

int main() {

	fin >> n >> m;
	for(int i = 0 ; i < KMAX; ++i)
		indexp[primes[i]] = i;

	for(int i = 1; i <= n; ++i) {
		
		fin >> v[i];
		int aux = v[i];
		int conf = 0;

		for(int j = 2; j * j <= aux; ++j) {

			int ok = 0;

			while(aux % j == 0) aux /= j, ok = 1;
			
			if(ok) 	
				conf |= (1 << indexp[j]);
		}

		if(aux > 1) {
			div1[i].push_back(aux);	
			if(aux <= 31)
				conf |= (1 << indexp[aux]);
		}

		div1[i].push_back(conf);
	}
	
	for(int i = 1; i <= m ; ++i)
		fin >> cost[i];

	int all = (1 << KMAX) - 1;
	int mincost = 0x3f3f3f3f;

	for(int i = 0 ; i <= all; ++i) {

		int c = 0;
		bool valid = true;
		memset(taken, 0, sizeof(taken));

		for(int j = 0 ; j < KMAX; ++j)
			if(i & (1 << j))
				c += cost[primes[j]];

		for(int j = 1; j <= n && valid == true; ++j) {

			int conf = div1[j][div1[j].size() - 1];

			if( (conf & i) != 0 ) continue;

			if(div1[j].size() > 1) {

				int big = div1[j][0];
				if(big <= 31) valid = false; 

				if(big > 31 && taken[big] == 0) {
					c += cost[big];
					taken[big] = 1;
				} 
			} else 
				valid = false;
		}

		if(valid == true && c < mincost)
			mincost = c;
	}

	fout << mincost << '\n';

	return 0;
}