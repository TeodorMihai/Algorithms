#include <bits/stdc++.h>

using namespace std;

const int NMAX = 200009;

int n;  int t[NMAX]; int root ;

vector<int> g[NMAX];

int viz[NMAX];

bool findRoot = false;

int cnt;


void dfs(int node) {

	if(findRoot == true) return ;

	viz[node] = 1;

	int x = t[node];

	if(viz[x] == 0)
		dfs(x);
	else if(viz[x] == 1) {
		cnt++;
		findRoot = true;
		root = node;
		t[node] = node;
	}

	viz[node] = 2;
}

void dfs2(int node) {

	viz[node] = 1;
	int x = t[node];


	if(viz[x] == 0)
		dfs2(x);
	else if(viz[x] == 1 && root != x) {
		cnt++;
		t[node] = root;
	}

	viz[node] = 2;
}

int main() {

	cin >> n ;

	for(int i = 1; i <= n; ++i) {

		cin >> t[i];

		if(t[i] == i)
			root = i;
	}

	if(root == 0) {

		for(int i = 1; i <= n; ++i)
			if(viz[i] == 0)
				dfs(i);
	}

	memset(viz, 0, sizeof(viz) );

	for(int i = 1; i <= n ; ++i)
		if(viz[i] == 0)
			dfs2(i);

	cout << cnt << '\n';

	for(int i = 1; i <= n ;++i)
		 cout << t[i] << ' ';

	cout << '\n';
	return 0;
}