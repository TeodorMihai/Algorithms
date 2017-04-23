#include <bits/stdc++.h>

using namespace std;

ifstream fin("pietre.in");
ofstream fout("pietre.out");

const int NMAX = 1e6 + 5;

int a; int b;

int mark[NMAX];
int per[NMAX];

int main() {

	int dif = 1;
	per[0] = 0;
	mark[0] = 1;

	for(int i = 1; i <= 1e6;  ++i)
		if(mark[i] == 0) {
			per[i] = i + dif;
			mark[i] = 1;
			if(i + dif <= 1e6)
				mark[i + dif] = 1;
			dif++;
		}

	int t;

	fin >> t;
	while(t--) {

		fin >> a >> b;
		if(a > b) swap(a, b);
		if(per[a] == b) 
			fout << 2 << '\n';
		else 
			fout << 1 << '\n';
	}

	return 0;
}