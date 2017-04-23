#include <bits/stdc++.h>

using namespace std;

ifstream fin("arbore3.in");
ofstream fout("arbore3.out");

const int NMAX = 1e6 + 5;
const int MOD = 666013;
 
int n; int s;
int v[NMAX]; int ans;
vector<int> h[MOD];
vector<int> g[NMAX];

int search(int x) {

	int key = x % MOD; int cnt = 0;
	if(key < 0) key += MOD;

	for(int y : h[key])
		if(y == x)
			cnt++;

	return cnt;
}

void insert(int x) {

	int key = x % MOD;
	if(key < 0) key += MOD;
	h[key].push_back(x);
}

void erase(int x) {

	int key = x % MOD;

	if(key < 0) key += MOD;

	for(int& y : h[key])
		if(y == x) {
			y = h[key][ h[key].size() - 1 ];
			h[key].pop_back();
			break;
		}
}


void dfs(int node, int sum) {

	sum += v[node];
	ans += search(sum - s);
	insert(sum);

	for(int x : g[node]) 
		dfs(x, sum);

	erase(sum);
}

int main() {

	fin >> n >> s;
	
	for(int i = 1; i <= n; ++i) {

		int fath; int value;
		fin >> fath >> value;
		g[fath].push_back(i);
		v[i] = value;
	}

	h[0].push_back(0);//cazul cand nu iau decat valoarea din nodul curent

	dfs(1, 0);

	fout << ans << '\n';

	return 0;
}