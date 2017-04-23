//in arbore retin pt fiecare pozitie lungimea maxima care se poate 
//forma cu pozitia aia
//interoghezi doar intervale pe care stiu ca pot obtine doar solutii valide =>
//sortare dupa capatul dreapta al intervalului
//se elimina posibile depasiri pe o directie prin faptul ca retii
//lungimile de la stanga la dreapta si alta prin faptul ca se sorteaza
//un interval nu e bagat pana nu are perechea 
#include <bits/stdc++.h>

using namespace std;

ifstream fin("pq.in");
ofstream fout("pq.out");

#define pp pair<int,int>

const int NMAX = 1e5 + 4;

int n; int m;

int v[NMAX];
int a[NMAX * 4];

vector<pp> g[NMAX];

int pos[NMAX];
int sol[NMAX];


void update(int nod, int st, int dr, int pos, int value) {

	if(st == dr) {
		a[nod] = max(a[nod], value);
		return ;
	}

	int mid = (st + dr) / 2;
	if(pos <= mid)
		update(nod * 2, st, mid, pos, value);
	else
		update(nod * 2 + 1, mid + 1, dr, pos, value);
	a[nod] = max(a[nod * 2], a[nod * 2 + 1]);
}


int query(int nod, int st, int dr, int l, int r) {

	if(l <= st && dr <= r)
		return a[nod];

	int mid = (st + dr) / 2;
	int res = 0;
	//st, mid , dr, intervalele nu sunt disjuncte niciodata
	if(l <= mid)
		res = query(nod * 2, st, mid, l, r);
	if(mid < r)
		res = max(res, query(nod * 2 + 1, mid + 1, dr, l, r));
	return res;
}

int main() {

	fin >> n >> m;
	for(int i = 1; i <= n; ++i)
		fin >> v[i];	

	for(int i = 1; i <= m ; ++i) {
		int a; int b; 
		fin >> a >> b;
		g[b].push_back({a, i});
	}

	for(int i = 1; i <= n; i++) {

		if(pos[v[i]])
			update(1, 1, n, pos[v[i]], i - pos[v[i]]);//pos, value
		pos[v[i]] = i;

		for(pp x : g[i])
			sol[x.second] = query(1, 1, n, x.first, i);
			
	}

	for(int i = 1; i <= m; ++i) {
		if(sol[i] == 0)
			fout << -1 << '\n';
				else 
			fout << sol[i] << '\n'; 
	}

	return 0;
}