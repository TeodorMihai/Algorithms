#include <bits/stdc++.h>

using namespace std;

ifstream fin("biscuiti.in");
ofstream fout("biscuiti.out");

typedef long long in64;

const int NMAX = 100009;
const in64 INF = (1ll << 60);

int n; int m;
in64 initialSum;
in64 sum;

struct Interval {

	in64 add;
	int indMin;
	in64 valMin;
	int viz;
};

Interval a[4 * NMAX];

in64 b[NMAX];

void update(int, int, int, int, int, in64);

void updateElem(int nod, int st, int dr, int pos) {

	if(st == dr) {
		a[nod].indMin = pos;
		a[nod].valMin = b[pos];
	} else {

		int mid = (st + dr) / 2;

		if(a[nod].viz == 1) {
			//am adaugat pe tot intervalul, minimul nu se schimba, propag schimbarea in jos pe 
			//lantul pe care am nevoie de ea
			update(nod * 2, st, mid, st, mid, a[nod].add);
			update(nod * 2 + 1, mid + 1, dr, mid + 1, dr, a[nod].add);
			a[nod].viz = 0;
			a[nod].add = 0;
		}


		if(pos <= mid)
			updateElem(nod * 2, st, mid, pos);
		else 
			updateElem(nod * 2 + 1, mid + 1, dr, pos);

		if( a[nod * 2].valMin <= a[nod * 2 + 1].valMin) {
			a[nod].indMin = a[nod * 2].indMin;
			a[nod].valMin = a[nod * 2].valMin;
		} else {
			a[nod].indMin = a[nod * 2 + 1].indMin;
			a[nod].valMin = a[nod * 2 + 1].valMin;
		}
	}
}

void update(int nod, int st, int dr, int left, int right, in64 add) {

	if(left <= st && dr <= right) {
		a[nod].add += add; 
		a[nod].valMin += add;
		a[nod].viz = 1;
		return ;
	}	

	int mid = (st + dr) / 2;

	if(a[nod].viz == 1) {

		//am adaugat pe tot intervalul, minimul nu se schimba, propag schimbarea in jos pe 
		//lantul pe care am nevoie de ea
		update(nod * 2, st, mid, st, mid, a[nod].add);
		update(nod * 2 + 1, mid + 1, dr, mid + 1, dr, a[nod].add);
		a[nod].viz = 0;
		a[nod].add = 0;
	}

	//st mid dr
	if(left <= mid)
		update(nod * 2, st, mid, left, right, add);

	if(mid + 1 <= right)
		update(nod * 2 + 1, mid + 1, dr, left, right, add);

	if( a[nod * 2].valMin <= a[nod * 2 + 1].valMin) {
		a[nod].indMin = a[nod * 2].indMin;
		a[nod].valMin = a[nod * 2].valMin;
	} else {
		a[nod].indMin = a[nod * 2 + 1].indMin;
		a[nod].valMin = a[nod * 2 + 1].valMin;
	}
}

int main() {

	fin >> n;

	for(int i = 1; i <= n; ++i) {
		
		fin >> b[i];
		initialSum += b[i];
		updateElem(1, 1, n, i);
	}

	for(int i = 1; i <= n; ++i) {
		sum += a[1].valMin;
		int pos = a[1].indMin;
		b[ pos ] = INF;
		updateElem(1, 1, n, pos);

		if(pos > 1)
			update(1, 1, n, 1, pos - 1, i);
	}

	fout << sum - initialSum << '\n'; 

	return 0;
}