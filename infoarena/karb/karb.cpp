#include <bits/stdc++.h>

using namespace std;

#define pp pair<int, int>

const int NMAX = 1e5 + 3 ;

int n; int m; int k;
vector< int > g[NMAX];
vector< pair<int, pp> > edges1;
vector< pair<int, pp> > edges0;

int comp[NMAX];
int t[NMAX]; int r1[NMAX]; int r2[NMAX];
int cnt;

void dfs(int node) {

	comp[node] = comp[0];

	for(int x : g[node])
		if(comp[x] == 0)
			dfs(x);
}

int root1(int x) {
	return comp[x] == x ? x : (comp[x] = root1(comp[x]));
}

int root2(int x) {
	return t[x] == x ? x : (t[x] = root2(t[x]));
}

void unite1(int a, int b) {

	if(r1[a] > r1[b]) 
		comp[b] = a;
	else  
		comp[a] = b;

	if(r1[a] == r1[b])
		r1[b]++;
}

void unite2(int a, int b) {

	if(r2[a] > r2[b]) 
		t[b] = a;
	else  
		t[a] = b;

	if(r2[a] == r2[b])
		r2[b]++;
}

struct cmp {

	bool operator()(const pair<int, pp>& e1, const pair<int, pp>& e2) {
		return e1.second.second < e2.second.second;
	}

} cmpU;

void solve() {

	for(int i = 1; i <= n; ++i)
		if(comp[i] == 0) {
			comp[0] = i;
			dfs(i);
		}

	for(int i = 1; i <= n; ++i)
		t[i] = i;

	for(int i = edges1.size() - 1; i >= 0 ; --i) {

			int x = edges1[i].first;
			int y = edges1[i].second.first;

			if(root1(x) != root1(y) ) {
				unite1(root1(x), root1(y));
				unite2(root2(x), root2(y));
				--k; cnt++;
				printf("%d %d\n", x, y);
			}
		}

	
	for(int i = edges1.size() - 1; i >= 0 ; --i) {

			int x = edges1[i].first;
			int y = edges1[i].second.first;

			if(k == 0) break;
			
			if(root2(x) != root2(y)  ) {
				unite2(root2(x), root2(y));
				--k; cnt++;
				printf("%d %d\n", x, y);
			}
		}

	for(int i = 0; i < edges0.size() ; ++i) {

		int x = edges0[i].first;
		int y = edges0[i].second.first;
		
		if(root2(x) != root2(y)) {

			unite2(root2(x), root2(y));
			printf("%d %d\n", x, y);
			cnt++;
		}

		if(cnt == n - 1) exit(0);
	}
}

int main() {

	freopen("karb.out", "w", stdout);
	freopen("karb.in", "r", stdin);


	scanf("%d%d%d", &n, &m , &k);
	edges0.reserve(m);
	edges1.reserve(m);

	for(int i = 1; i <= m; ++i) {
		int x; int y; int w;
		scanf("%d%d%d", &x, &y, &w);

		if(w == 1)
			edges1.push_back({x, {y, w}});
		else {
			
			edges0.push_back({x, {y, w}});
			g[x].push_back(y);
			g[y].push_back(x);
		}
	}

	solve();

	fclose(stdout);

	return 0;
}