#include <bits/stdc++.h>

using namespace std;

ifstream fin("arbint.in");
ofstream fout("arbint.out");

const int NMAX = 100009;

int n; int m;
int a[NMAX];
int aib[NMAX];

int query(int st, int dr) {

	int m = 0; int q;

	for(int p = dr - (dr & -dr) ; st <= dr; dr = p , p -= p & -p) {
		//am intervalul [p + 1, dr] in aib[dr]
		if(p + 1 >= st) //intervalul interogat e inclus in cel initial
			q = aib[dr];//query pe tot intervalul
		else 
			q = (p = dr - 1) + 1;//query doar pe elementul curent

		if(a[q] > a[m])
			m = q;
	}

	return m;
}

int update(int pos) {

	for(int x = pos; pos <= n; pos += pos & -pos) {
		if(aib[pos] == x) { //maximul de pe intervalul curent este fix elementul schimbat
			
			int newM = query(pos - (pos & -pos) + 1, pos - 1);//fac query pe restul intervalului
			
			aib[pos] = (a[newM] > a[pos]) ? newM : pos;

		} else if(a[x] > a[aib[pos]])
			aib[pos] = x;
	}
}

int main() {
	
	fin >> n >> m ;

	for(int i = 1; i <= n ; ++i) {
		fin >> a[i];
		update(i);
	}

	aib[0] = -0x3f3f3f3f;//cand fac query pe un interval fara niciun element
	
	for(int i = 1; i <= m; ++i) {
		int x; int y; int type;
		fin >> type;
		fin >> x >> y;
		if(type == 0)
			fout << a[query(x, y)] << '\n';
		if(type == 1)
			a[x] = y, update(x);
	}
	

	return 0;
}