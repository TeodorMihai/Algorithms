#include <bits/stdc++.h>

using namespace std;

ifstream fin("scmax.in");
ofstream fout("scmax.out");

const int NMAX = 1e5 + 5;

int n;
int v[NMAX];
int lst[NMAX];
int aib[NMAX];

int bit(int x) { return x & -x; }

struct Cmp {

	bool operator()(const int x, const int y) {
		return v[x] < v[y];
	}
} cmp;

void ins(int pos, int value) {

	for( ; pos <= n ; pos += bit(pos))
		aib[pos] = max(aib[pos], value);
}

int query(int pos) {

	int ans = 0;

	for( ; pos ; pos -= bit(pos))
		ans = max(aib[pos], ans);

	return ans;
}

int main() {

	fin >> n; 

	for(int i = 1; i  <= n ; ++i) {
		fin >> v[i];
		lst[i] = v[i];
	}

	sort(lst + 1, lst + 1 + n);

	for(int i = 1; i <= n ; ++i)
		v[i] = lower_bound(lst + 1, lst + 1 + n, v[i]) - lst;
	//cate elemente sunt mai mici decat v[i]
	
	int sol = 0;

	for(int i = 1; i <= n ; ++i) {

		int best = query(v[i] - 1);
		ins(v[i], best + 1);

		if(best + 1 > sol)
			sol = best + 1;
	}

	fout << sol << '\n';



	return 0;	
}