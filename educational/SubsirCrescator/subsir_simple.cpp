#include <bits/stdc++.h>

using namespace std;

ifstream fin("scmax.in");
ofstream fout("scmax.out");

const int NMAX = 100001;

int n; 

int v[NMAX];

int best[NMAX];//best[i] = ultimul element(si cel mai mic posibil ) pentru un sir de lungime i pana la momentul actual
//best[0] = lungimea celui mai lung subsir format pana acum

int ret[NMAX];

vector<int> sol;

int binarys(int x) {

	int pos; int byte = 1;

	for(; byte <= best[0]; byte <<= 1);

	for(pos = 0; byte ; byte >>= 1)
		if(pos + byte <= best[0] && best[pos + byte] < x)
			pos += byte;

	return pos;
}


int main() {

	fin >> n;

	for(int i = 1 ; i <= n ; ++i) {

		fin >> v[i];
		best[i] = -1;
	}

	best[0] = 1;
	best[1] = v[1];
	ret[1] = 1;

	for(int i = 2; i <= n ; ++i) {

		 int  ind = binarys(v[i]);

		 ret[i] = ind + 1;
		 
		 if(best[ind + 1] == -1)
		 	best[0]++;
		 
		 best[ind + 1] = v[i];

	}

	fout << best[0] << '\n';

	for(int i = n ; i > 0 ; --i)
		if(best[0] == ret[i]) {

			sol.push_back(i);
			best[0]--;
		}
	for(int i  = sol.size() - 1 ; i >= 0 ; --i)
		fout << v[sol[i]] << " ";


	return 0;
}