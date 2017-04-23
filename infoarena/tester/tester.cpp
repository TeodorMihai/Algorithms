//merge mai bine o parcurgere dupa muchii daca stergi muchiile efectiv,
//nu doar le marchezi ca vizitate, daca graful e dens
#include <bits/stdc++.h>

using namespace std;

ifstream fin("tester.in");
ofstream fout("tester.out");

#define pp pair<int, int>

const int NMAX = 505;
const int MMAX = 5005;

int n; int m;

vector<pp> g[NMAX];
vector<pp> gt[NMAX];
vector<pp> edges;
vector<int> g2[MMAX];
vector<int> sol;

int in[MMAX];
int out[MMAX];

stack<int> s;

void read() {

	fin >> n >> m ;

	for(int i = 1; i <= m ; ++i) {
		int x, y; fin >> x >> y;
		g[x].push_back({y, i});
		gt[y].push_back({x, i});
		edges.push_back({x, y});
	}
}

void dfs(int node) {

	s.push(node);

	while(s.empty() == false) {

		int node = s.top();

		if(g2[node].size() == 0) {
			sol.push_back(node); 
			s.pop();
		} else {
			
			int x = g2[node][ g2[node].size() - 1];
			g2[node].pop_back();
			s.push(x);
		}

	}
}

void solve() {

	int cnt = 0;

	for(int i = 1; i <= n ; ++i) {

		for(pp x : g[i])
			for(pp y : gt[i]) 
				if(y.second != x.second) {
					g2[y.second].push_back(x.second);
					out[y.second]++;
					in[x.second]++;
					cnt++;
				}
				
	}

	for(int i = 1; i <= m; ++i)
		if(in[i] > out[i]) {
			for(int j = 1; j <= in[i] - out[i]; ++j)
				g2[i].push_back(0);
		} else if(in[i] < out[i])
			for(int j = 1; j <= out[i] - in[i]; ++j)
				g2[0].push_back(i);

	dfs(0);

	reverse(sol.begin(), sol.end());

	for(int i = 0 ; i < sol.size(); ++i) {

		int x = sol[i];
		if(x == 0) {
			if(i != 0 && i != sol.size() - 1) 
				fout << "R ";
		} else {
			if(sol[i - 1] == 0)
				fout << edges[x - 1].first << ' ' << edges[x - 1].second << ' ';
				//written = sprintf(buffer + ind, "%d %d ", edges[x - 1].first , edges[x - 1].second);
			else
				fout << edges[x - 1].second << ' ';
				//written = sprintf(buffer + ind, "%d ", edges[x - 1].second);
		}
	}
		
}

int main() {

	read(); solve();

	return 0;
}