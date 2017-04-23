#include <bits/stdc++.h>

using namespace std;

ifstream fin("dfs.in");
ofstream fout("dfs.out");

const int NMAX = 100001;

class Graph {

public:
	vector<int> g[NMAX];
	int mark[NMAX];
	int n;
	int m;

} ;



void dfs(Graph& graph, int x) {

	graph.mark[x] = 1;

	for(unsigned i = 0 ; i < graph.g[x].size() ; ++i){
		if(graph.mark[ graph.g[x][i] ] == 0)
			dfs(graph, graph.g[x][i]);
	}
}


int main() {


	int cnt = 0;
	Graph graph;	
	
	memset(graph.mark, NMAX, 0);

	fin >> graph.n >> graph.m;

	for(int i = 1; i <= graph.m; ++i) {

		int x; int y;
		fin >> x >> y;

		graph.g[x].push_back(y);
		graph.g[y].push_back(x);

	}
	for(int i = 1; i <= graph.n ; ++i)
		if(graph.mark[i] == 0)
			dfs(graph,  i), ++cnt;

	fout << cnt << '\n'; 

	return 0;
}