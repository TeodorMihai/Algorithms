#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5 + 5;
const int INF = 1e9 + 5;

int n; int m; int k;

bool storage[NMAX];
vector< pair<int, int> > g[NMAX];

int main() {

	cin >> n >> m >> k;

	for(int i = 1; i <= m ; ++i) {
		int x; int y; int c;
		cin >> x >> y >> c;
		g[x].push_back({y, c});
		g[y].push_back({x, c});
	}

	for(int i = 1; i <= k ; ++i) {
		int x;  cin >> x;
		storage[x] = 1;
	}

	int mini = INF;

	for(int i = 1; i <= n ; ++i) {

		for(pair<int, int> p : g[i])
			if(storage[i] == 1 && storage[p.first] == 0 && p.second < mini )
				mini = p.second;
	}

	if(mini == INF) 
		cout <<  -1 << '\n';
	else 
		cout << mini << '\n';

	return 0;
}