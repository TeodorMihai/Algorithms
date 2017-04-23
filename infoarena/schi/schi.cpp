//parcurg locurile in ordine inversa si odata un loc luat il sterg din clasament
//la fiecare query gasesc al k-lea loc neocupat, k = v[i]
#include <bits/stdc++.h>

using namespace std;

ifstream fin("schi.in");
ofstream fout("schi.out");

const int NMAX = 30009;

int n;
int a[NMAX * 4];
int v[NMAX];
int ind[NMAX];

void query(int nod, int st, int dr, int pos, int concurent) {

	if(st == dr) {
		a[nod] = 0;
		ind[st] = concurent;
		return ;
	}

	int mid = (st + dr) / 2;

	if(a[nod * 2] >= pos)
		query(nod * 2, st, mid, pos, concurent);
	else 
		query(nod * 2 + 1, mid + 1, dr, pos - a[nod * 2], concurent);
	a[nod] = a[nod * 2] + a[nod * 2 + 1];
}


void build(int nod, int st, int dr) {

	if(st == dr)
		a[nod] = 1;
	else {

		int mid = (st + dr) / 2;

		build(nod * 2, st, mid);
		build(nod * 2 + 1, mid + 1, dr);
		a[nod] = a[nod * 2] + a[nod * 2 + 1];
	}
}

int main() {

	fin >> n;

	for(int i = 1; i <= n ; ++i)
		fin >> v[i];
	build(1 , 1, n);
	for(int i = n; i ; --i) {

		query(1, 1, n, v[i], i);
		
	}

	for(int i = 1; i <= n ; ++i)
		fout << ind[i] << '\n';


	return 0;
}