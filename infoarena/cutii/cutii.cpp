#include <bits/stdc++.h>

using namespace std;

ifstream fin("cutii.in");
ofstream fout("cutii.out");

const int NMAX = 3509;

vector< tuple < int, int, int > > v;

int n; int t;
int aib[NMAX][NMAX];

void read() {


	v.clear();

	for(int i = 1; i <= n; ++i) {
		
		int x; int y; int z;

		fin >> x >> y >> z;

		v[i] = make_tuple(x, y, z);
	}
}

int bit(int x) { return x & (-x); }

void update(int posX, int posY, int val) {

	int py = posY;

	while(posX <= n) {

		py = posY;

		while(py <= n) {

			aib[posX][py] = max(aib[posX][py], val);

			py += bit(py);
		}

		posX += bit(posX);
	}
}

void putZero(int posX, int posY) {

	int py = posY;

	while(posX <= n) {

		py = posY;

		while(py <= n) {

			aib[posX][py] = 0;

			py += bit(py);
		}

		posX += bit(posX);
	}
}

int query(int posX, int posY) {

	int py = posY;
	int maxi = 0;

	while(posX > 0) {

		py = posY;

		while(py > 0) {

			maxi = max(aib[posX][py], maxi);
			py -= bit(py);
		}

		posX -= bit(posX);
	}

	return maxi;
}

void clearAib() {

	for(int i = 1; i <= n; ++i)
		putZero(get<1>(v[i]), get<2>(v[i]));
}

int solve() {

	sort(&v[1], &v[n + 1], [] (tuple<int, int, int> a, tuple<int, int, int> b) -> bool {
		return get<0>(a) < get<0>(b);
	});

	int maxi = -1;

	for(int i = 1; i <= n; ++i) {

		int best = query( get<1>(v[i]) - 1 , get<2>(v[i]) - 1);

		update(get<1>(v[i]), get<2>(v[i]), best + 1);

		if(maxi < best + 1)
			maxi = best + 1;
	}

	return maxi;
}


int main() {

	fin >> n >> t;
	
	v.reserve(NMAX);

	while(t--) {

		read();
		fout << solve() << '\n'; 

		clearAib();
	}

	return 0;
}