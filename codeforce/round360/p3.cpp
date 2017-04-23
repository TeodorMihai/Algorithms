#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100009;

vector<int> g[NMAX];

int n; int m;
int viz[NMAX];
int s[NMAX];

bool pos = true;

void read() {

	cin >> n >> m;

	for(int i = 1; i <= m; ++i) {
		int x; int y;
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
}

void dfs(int nod, int h) {

	viz[nod] = 1;

	if(h % 2 == 0)
		s[nod] = 1;
	else 
		s[nod] = 2;

	for(int x : g[nod])
		if(viz[x] == 0)
			dfs(x, h + 1);
		else if(s[x] == s[nod])
			pos = false;
}

void solve() {

	for(int i = 1; i <= n; ++i)
		if(viz[i] == 0)
			dfs(i, 0);
}

void print() {

	int cnt = 0;
	for(int i = 1; i <= n; ++i)
		if(s[i] == 1)
			cnt++;
	if(pos == false) {
		cout << -1 << '\n'; 
		return;
	} 

	cout << cnt << '\n'; 
	for(int i = 1; i <= n ; ++i)
		if(s[i] == 1)
			cout << i << ' ';

	cout << '\n' << n - cnt << '\n';

	for(int i = 1; i <= n ; ++i)
		if(s[i] == 2)
			cout << i << ' ';

	cout << '\n'; 
}

int main() {

	read();
	solve();
	print();

	return 0;
}