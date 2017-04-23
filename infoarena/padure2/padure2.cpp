#include <bits/stdc++.h>

using namespace std;

ifstream fin("padure2.in");
ofstream fout("padure2.out");

const int NMAX = 1e6 + 6;
const int CMAX = 1002;
const int MOD = 2000003;

#define point pair<int, int>
#define x first
#define y second

int n; int m;

int c;

vector<point> v;

int fact[NMAX * 2];
int pos[CMAX];

//a ^ MOD - 2
int inv(int a) {

	int put[32];

	put[0] = a;

	for(int i = 1; i < 32; ++i)
		put[i] = (1ll * put[i - 1] * put[i - 1]) % MOD;

	int rez = 1;
	for(int i = 0 ; i < 32; ++i)
		if( (1 << i) & (MOD - 2))
			rez = (1ll * rez * put[i]) % MOD;

	return rez;
}

int comb(int a, int b) {

	//a! / b! * (a - b)!
	return 1ll * fact[a] * inv(fact[b]) % MOD * inv(fact[a - b]) % MOD;
}

struct cmp {

	bool operator()(const point& p1, const point& p2) {
		if(p1.x == p2.x)
			return p1.y < p2.y;
		return p1.x < p2.x;
	}
} cmpX;

int solve() {

	v.push_back({n, m});
			
	for(unsigned i = 0 ; i < v.size(); ++i) {

		pos[i] = comb(v[i].x + v[i].y - 2, v[i].x - 1);

		for(unsigned int  j = 0; j < i ; ++j) {

			if(v[i].x >= v[j].x && v[i].y >= v[j].y) {
				int dx = v[i].x - v[j].x + 1;
				int dy = v[i].y - v[j].y + 1;

				pos[i] -= 1ll * pos[j] * comb(dx + dy - 2, dx - 1) % MOD;
				if(pos[i] < 0)
					pos[i] += MOD;
			}
		}
	}

	return pos[v.size() - 1];
}

int main() {

	fin >> n >> m;

	fin >> c;

	for(int i = 0; i < c; ++i) {
		int xc , yc; fin >> xc >> yc;
		v.push_back({xc, yc});
	}
	
	sort(v.begin(), v.end(), cmpX);

	fact[0] = fact[1] = 1;
	for(int i = 2; i <= n + m; ++i)
		fact[i] = (1ll * fact[i - 1] * i) % MOD;

	fout << solve() << '\n';

	return 0;
}