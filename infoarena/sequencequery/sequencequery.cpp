#include <bits/stdc++.h>

using namespace std;

ifstream fin("sequencequery.in");
ofstream fout("sequencequery.out");

typedef int64_t in64;

const int NMAX = 100009;
const in64 INF = (1 << 30);

int n; int m;

struct Interval {

	in64 sum;
	in64 sl;
	in64 sr;
	in64 seq;

	Interval() : sum(-INF) , sl(-INF), sr(-INF), seq(-INF) { }
	Interval(in64 _sum, in64 _sl, in64 _sr, in64 _seq) : sum(_sum), sl(_sl) , sr(_sr), seq(_seq) { }
};

Interval a[NMAX * 4];

Interval update(int nod, int st, int dr, int pos, int value) {

	if(st == dr) {

		a[nod].sum = a[nod].sl = a[nod].sr = a[nod].seq = value; //minimum 1 element
		return a[nod];
	}
	
	int mid = (st + dr) / 2;
	
	if(pos <= mid)
		a[nod * 2] = update(nod * 2, st, mid, pos, value);
	else 
		a[nod * 2 + 1] = update(nod * 2 + 1, mid + 1, dr, pos, value);

	a[nod].seq = max(a[nod * 2].seq, a[nod * 2 + 1].seq);
	if(a[nod].seq < a[nod * 2].sr + a[nod * 2 + 1].sl)
		a[nod].seq = a[nod * 2].sr + a[nod * 2 + 1].sl;

	a[nod].sum = a[nod * 2].sum + a[nod * 2 + 1].sum;
	a[nod].sl = max(a[nod * 2].sl , a[nod * 2].sum + a[nod * 2 + 1].sl);
	a[nod].sr = max(a[nod * 2 + 1].sr, a[nod * 2 + 1].sum + a[nod * 2].sr);

	return a[nod];
}

Interval query(int nod, int st, int dr, int left, int right) {

	if(left <= st && dr <= right)
		return a[nod];

	int mid = (st + dr) / 2;

	//st mid dr
	Interval l;
	Interval r;
	Interval x;

	if(left <= mid)
		l = query(nod * 2, st , mid, left, right);
	if(mid + 1 <= right)
		r = query(nod * 2 + 1, mid + 1, dr, left, right);
	 	
	x.seq = max(l.seq, max(r.seq, l.sr + r.sl));
	x.sl = max(l.sum + r.sl, l.sl);
	x.sr = max(r.sum + l.sr, r.sr);
	x.sum = l.sum + r.sum;

	return x;
}

int main() {

	fin >> n >> m;

	for(int i = 1; i <= n ; ++i) {
		int x; fin >> x;
		update(1, 1, n, i, x);
	}

	while(m--) {
		int x; int y;
		fin >> x >> y;
		Interval q = query(1, 1, n, x, y);
		fout << q.seq << '\n'; 
	}	
	return 0;
}