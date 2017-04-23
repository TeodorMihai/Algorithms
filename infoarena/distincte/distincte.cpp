#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5 + 5;
const int MOD = 666013;

#define pp pair<int, int>
#define x first
#define y second

int n; int m; int k;

int v[NMAX];
int aib[NMAX];//aib[i] = suma [i - 2 ^ bit(i) + 1 , i]
int sol[NMAX];
int last[NMAX];

vector<pp> query[NMAX];

inline int bit(int x) { return x & -x; }

void ins(int pos, int value) {

	for( ; pos <= n ; pos += bit(pos)) {
		
		aib[pos] += value;

		if(aib[pos] >= MOD)
			aib[pos] -= MOD;
     	else if(aib[pos] < 0)
			aib[pos] += MOD;
	}
}

int que(int pos) {

	int sum = 0;

	for( ; pos > 0; pos -= bit(pos)) {
		sum += aib[pos];
		if(sum >= MOD)
			sum -= MOD;
	}

	return sum;
}

int main() {

	freopen("distincte.in", "r", stdin);
	freopen("distincte.out", "w", stdout);

	scanf("%d%d%d", &n, &k, &m);

	for(int i = 1; i <= n; ++i)
		scanf("%d", &v[i]);
	
	for(int i = 1; i <= m ; ++i) {
		int st; int dr; 
		scanf("%d%d", &st, &dr);
		query[dr].push_back({st, i});
	}

	for(int i = 1; i <= n ; ++i) {

		ins(i, v[i]);

		if(last[v[i]])
			ins(last[v[i]], -v[i]);

		last[v[i]] = i;

		for(pp p : query[i]) {

			sol[p.y] = que(i) - que(p.x - 1);
			if(sol[p.y] < 0) sol[p.y] += MOD;
		}
	}

	for(int i = 1; i <= m ; ++i)
		printf("%d\n", sol[i]);

	return 0;
}