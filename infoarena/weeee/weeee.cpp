#include <bits/stdc++.h>

using namespace std;

ifstream fin("weeee.in");
ofstream fout("weeee.out");

const int NMAX = 200009;

int n;

char v[NMAX];

int st[NMAX];
int dr[NMAX];

int main() {

	fin >> n;

	fin >> v;

	for(int i = 0 ; i < n ; ++i) {
		if(v[i] == 'E') 
			st[i] = st[i - 1] + 1;
		else 
			st[i] = st[i - 1];
	}
	bool e = false;
	bool w = false;


	for(int i = n - 1; i >= 0 ; --i) {

		if(v[i] == 'E')
			e = true;

		if(v[i] == 'W')
			w = true;

		if(v[i] == 'E')
			dr[i] = dr[i + 1] + 1;
		else 
			dr[i] = dr[i + 1];
	}
		//dr[i] = cati de E am la dreapta inclusiv

		//st[i] = cati E am la stanga inclusiv

		//niciodata W nu trece peste W, trece doar peste E-uri, alegeam partea in care
		//sunt cele mai putine e-uri
	if(w == false || e == false) {
		fout << -1 << '\n'; 
		return 0;
	}

	long long cost = 0;
	bool firstW = false;
	
	for(int i = 0 ; i < n ; ++i)
		if(v[i] == 'W') {

			if(firstW == false)
				cost += 1ll * st[i];
			else 
				cost += 1ll * min(st[i], dr[i]);
			firstW = true;
		}
	fout << cost << '\n'; 

	return 0;
}