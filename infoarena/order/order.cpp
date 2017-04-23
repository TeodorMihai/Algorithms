#include <bits/stdc++.h>

using namespace std;

ifstream fin("order.in");
ofstream fout("order.out");

const int NMAX = 30009;

int n;
int aib[NMAX * 2];

int bit(int x) { return x & (-x); }

void update(int pos, int val) {

	for( ; pos <= 2 * n; pos += bit(pos) ) 
		aib[pos] += val;
}

int query(int pos) {

	int sum = 0;

	for( ; pos > 0 ; pos -= bit(pos) )
		sum += aib[pos];

	return sum;
}

int getInterval(int start, int sum) {

	sum += query(start);

	int pos = 0; int step;

	for(step = 1; step <= 2 * n; step <<= 1);

	for( ; step; step >>= 1)
		if(pos + step <= 2 * n && query(pos + step) < sum)
			pos += step;
	return pos + 1;
}

int main() {

	fin >> n;

	for(int i = 1; i <= 2 * n ; ++i) 
		update(i, 1);

	int taken = 0; 
	int last = 1;
	int next = 1;
	int pos = 0;
	int left = n;

	for(int i = 1; taken < n; taken++, i++) {

		pos = getInterval(last, i % left == 0 ? left : (i % left) );
		//vreau sa iau i numere incepand cu last, fara el
		pos = pos % n == 0 ? n : pos % n;
		last = pos;//2 4 7 11

		update(pos, -1);
		update(pos + n, -1); 
		left--;

		fout << last << ' ' ;
		
	}

	return 0;
}