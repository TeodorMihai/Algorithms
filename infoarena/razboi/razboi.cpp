#include <bits/stdc++.h>

using namespace std;

ifstream fin("razboi.in");
ofstream fout("razboi.out");

const int NMAX = 16009;

int t; int n;

vector< pair<int, int> > g[NMAX];

int viz[NMAX]; int dist[NMAX];

int prev1[NMAX];
int cost[NMAX];

void read() {

	fin >> n;
	
	memset(viz, 0, sizeof(viz));
	memset(dist, 0, sizeof(dist));
	memset(prev1, 0, sizeof(prev1));
	memset(cost, 0, sizeof(cost));

	for(int i = 1; i <= n ; ++i)
		g[i].clear();

	for(int i = 1; i < n ; ++i) {
		int x; int y; int d;
		fin >> x >> y >> d;
		g[x].push_back({y, d});
		g[y].push_back({x, d});
	}
}

void dfs(int x) {

	viz[x] = 1;

	for(auto node : g[x]) 
		if(viz[node.first] == 0) {

			dist[node.first] = dist[x] + node.second;
			prev1[node.first] = x; 
			cost[node.first] = node.second;

			dfs(node.first);
		}
}

void solve(int test) {

	prev1[1] = 0;
	dfs(1);

	int indmax = 1;

	for(int i = 1; i <= n ; ++i) {

		//cout << i << ' ' << dist[i] << '\n';

		if(dist[indmax] < dist[i]) 
			indmax = i;
	}

	dist[indmax] = 0;
	memset(prev1, 0, sizeof(prev1));
	memset(cost, 0, sizeof(cost));
	memset(viz, 0, sizeof(viz));

	dfs(indmax);

	int start = indmax;

	for(int i = 1; i <= n ; ++i) {
		if(dist[i] > dist[indmax])
			indmax = i;
	}

	//start -> indmax drumul maxim

	int minD = 0x3f3f3f3f;
	int sum = 0;
	int total = dist[indmax];

	vector<int> sol;

	while(indmax) {

		if( max(sum, total - sum) == minD) 
			sol.push_back(indmax);

		if(sum < minD && (total - sum) < minD) {
			sol.clear();
			sol.push_back(indmax);
			minD = max(sum, total - sum);
		}
		
		sum += cost[indmax];
		indmax = prev1[indmax];
	}
	fout << "Testul nr #" << test << '\n';
	sort(sol.begin(), sol.end());
	for(int x : sol)
		fout << x << '\n';
}

int main() {

	fin >> t;

	for(int i = 1;  i <= t; ++i) {
		read();
		solve(i);
	}

	return 0;
}