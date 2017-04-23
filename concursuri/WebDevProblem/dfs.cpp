#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;


ifstream fin ("hamilton.in");
ofstream fout ("hamilton.out");

const int NMAX = 19;


int N;  int M;

vector<pair <int,int> > G[NMAX];

int viz[NMAX];

int sum = 0 ; int min_sum = -(1<<29);

void read() {


	fin >> N >> M; 
	for(int i = 1; i <= M; ++i)  {

		int x; int y; int cost;
		fin >> x >> y >> cost;
		G[x].push_back(make_pair( y, cost ) );

	}
}

void dfs(int x, int deep) {

	viz[x] = 1;

	if(deep == N && x == 1)
		min_sum = min(min_sum, sum);

	for(unsigned i = 0 ; i < G[x].size(); ++i) {

		int node = G[x][i].first;
		int cost = G[x][i].second;

		if(viz[node] == 0) {

			sum += cost;
			dfs(node, deep + 1);
			sum -= cost;
		}
	}
}


int main() {

	read();

	dfs(1, 1);

	fout << min_sum << '\n';
	return 0;
}