#include <bits/stdc++.h>

using namespace std;

const int NMAX = 300009;
const int INF = 0x3f3f3f3f;

int n; 

struct Query {

	int type;
	int x;
};

Query v[NMAX];
int ind[NMAX];

struct Interval {
	int in; //daca exista un element in interval => in == 1
	int mini;
	int maxi;
	int minDif;

	Interval() : in(0), mini(INF), maxi(0), minDif(INF) { }
};

int cnt;

Interval *a;

void read() {

	char s[100];

	while(fgets(s, 100, stdin)) {

		if(s[0] == 'I')
			v[++n].type = 1, v[n].x = atoi(s + 1);
		if(s[0] == 'S')
			v[++n].type = 2, v[n].x = atoi(s + 1);
		if(s[0] == 'C')
			v[++n].type = 3, v[n].x = atoi(s + 1);
		if(s[0] == 'M')
			if(s[1] == 'A')
				v[++n].type = 4;
			else 
				v[++n].type = 5;
	}
}

struct cmp {

	bool operator ()(int x, int y) {
		if(v[x].type > 3)
			return false;
		if(v[y].type > 3)
			return true;

		return v[x].x < v[y].x;
	}
} comp;

int bs(int x) {

	int step; int pos;

	for(step = 1; step <= n; step <<= 1);

	for(pos = 1 ; step ; step >>= 1)
		if(pos + step <= n && v[ind[pos + step]].type <= 3 && v[ ind[pos + step] ].x <= x)
			pos += step; 
	return pos;
	
}

void insert(int nod, int st, int dr, int pos, int value) {

	if(st == dr) {

		a[nod].in = 1;
		a[nod].mini = value;
		a[nod].maxi = value;
		a[nod].minDif = INF;
		return ;
	}

	int mid = (st + dr) / 2;

	if(pos <= mid)
		insert(nod * 2, st, mid, pos, value);
	if(mid + 1 <= pos)
		insert(nod * 2 + 1, mid + 1, dr, pos, value);

	a[nod].in = a[nod * 2].in || a[nod * 2 + 1].in;

	a[nod].mini = a[nod * 2].in == 1 ? a[nod * 2].mini : INF;
	if(a[nod * 2 + 1].in == 1 && a[nod * 2 + 1].mini <= a[nod].mini)
		a[nod].mini = a[nod * 2 + 1].mini;

	a[nod].maxi = a[nod * 2].in == 1 ? a[nod * 2].maxi : 0;
	if(a[nod * 2 + 1].in == 1 && a[nod * 2 + 1].maxi >= a[nod].maxi)
		a[nod].maxi = a[nod * 2 + 1].maxi;

	a[nod].minDif = min(a[nod * 2].minDif, a[nod * 2 + 1].minDif);
	if(a[nod * 2].in == 1 && a[nod * 2 + 1].in == 1)
		a[nod].minDif = min( a[nod].minDif, abs(a[nod * 2].maxi - a[nod * 2 + 1].mini));
}

int sterge(int nod, int st, int dr, int pos) {

	if(st == dr) {

		a[nod].mini = INF;
		a[nod].maxi = 0;
		a[nod].minDif = INF;
		if(a[nod].in == 0)
			return -1;
		return (a[nod].in = 0);
	}

	int mid = (st + dr) / 2;

	int x = 0;

	if(pos <= mid)
		x = sterge(nod * 2, st, mid, pos);
	if(mid + 1 <= pos)
		x = sterge(nod * 2 + 1, mid + 1, dr, pos);

	a[nod].in = a[nod * 2].in || a[nod * 2 + 1].in;

	a[nod].mini = a[nod * 2].in == 1 ? a[nod * 2].mini : INF;
	if(a[nod * 2 + 1].in == 1 && a[nod * 2 + 1].mini <= a[nod].mini)
		a[nod].mini = a[nod * 2 + 1].mini;

	a[nod].maxi = a[nod * 2].in == 1 ? a[nod * 2].maxi : 0;
	if(a[nod * 2 + 1].in == 1 && a[nod * 2 + 1].maxi >= a[nod].maxi)
		a[nod].maxi = a[nod * 2 + 1].maxi;

	a[nod].minDif = min(a[nod * 2].minDif, a[nod * 2 + 1].minDif);
	if(a[nod * 2].in == 1 && a[nod * 2 + 1].in == 1)
		a[nod].minDif = min(a[nod].minDif, abs(a[nod * 2].maxi - a[nod * 2 + 1].mini));
	return x;
}

int cauta(int nod, int st, int dr, int pos) {

	if(st == dr)
		return a[nod].in;

	int mid = (st + dr) / 2;

	int x = 0;

	if(pos <= mid)
		x = cauta(nod * 2, st, mid, pos);
	if(mid + 1 <= pos)
		x = cauta(nod * 2 + 1, mid + 1, dr, pos);

	return x;

}

void solve() {

	for(int i = 1; i <= n; ++i)
		ind[i] = i;

	sort(ind + 1, ind + 1 + n, comp);

	for(int i = 1; i <= n; ++i)
		if(v[i].type != 5 && v[i].type != 4)
			cnt++;

	a = new Interval[cnt * 4 + 10];

	for(int i = 1; i <= n; ++i) {
		if(v[i].type == 1 || v[i].type == 2 || v[i].type == 3) {

			int pos = bs(v[i].x);

			if(v[i].type == 1)
				insert(1, 1, cnt, pos, v[i].x);
			if(v[i].type == 2 && sterge(1, 1, cnt, pos) == -1)
				printf("%d\n", -1);
			if(v[i].type == 3)
				printf("%d\n", cauta(1, 1, cnt, pos));
		}
		if(v[i].type == 4) {
			if(a[1].minDif != INF)
				printf("%d\n", a[1].maxi - a[1].mini);
			else 
				printf("%d\n", -1);
		}

		if(v[i].type == 5) {
			if(a[1].minDif != INF)
				printf("%d\n", a[1].minDif);
			else 
				printf("%d\n", -1);
		}
	}
}

int main() {

	freopen("zeap.in", "r", stdin);
	freopen("zeap.out", "w", stdout);

	read();
	solve();

	return 0;
}