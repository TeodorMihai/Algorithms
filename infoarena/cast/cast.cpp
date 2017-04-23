#include <bits/stdc++.h>

using namespace std;

ifstream fin("cast.in");
ofstream fout("cast.out");

const int NMAX = 12;
const int INF = 0x3f3f3f3f;

int n;
int a[NMAX][NMAX];
int d[1<<NMAX][NMAX];
//orice metoda de a ajunge la rezultatul final reducand problema
//structura de arbore a solutiei => dinamica pe tipul arbore, subarbore + restul
//e si impartibila in multimi => dinamica de O(n^3)

int main() {

	int t;
	fin >> t;
	while(t--) {

		fin >> n;

		for(int i = 0 ; i < n; ++i)
			for(int j = 0 ; j < n; ++j)
				fin >> a[i][j];

		int all = (1 << n) - 1;
		for(int i = 1; i <= all; ++i) 
			for(int j = 0 ; j < n ; ++j) {

				if( ( (1 << j) & i ) == 0) continue;

				if(i == (1 << j) ) { d[i][j] = 0; break; }

				d[i][j] = INF;

				int p = i - (1 << j);
				int ci = ~p;

				for(int k = 0 ; k < p ; k = (k + ci + 1) & ~ci) {
					
					int aux = k;
					if(k == 0) k = p;

					if( (k | p) != p) continue; //k nu contine j, este submultime a lui i

					for(int q = 0 ; q < n; ++q) {

						if( ( (1 << q) & k ) == 0 ) continue; //k contine q
						int complement = i - k;

						d[i][j] = min(d[i][j], a[j][q] + max(d[k][q], d[complement][j]));
					}

					if(aux == 0) k = 0;
				}
			}

		fout << d[all][0] << '\n';
	}

	return 0;
}