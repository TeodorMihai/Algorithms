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

int s[20];

int viz[NMAX];

 int min_sum = (1<<29);

void read() {


	fin >> N >> M; 

	for(int i = 1; i <= M; ++i)  {

		int x; int y; int cost;
		fin >> x >> y >> cost;
		G[x].push_back(make_pair( y, cost ) );

	}

}

void dfs(int x, int deep, int sum) {


	if(deep == N + 1 && x == 1) {

		min_sum = min(min_sum, sum);
			
		return ;	
	}

	for(unsigned i = 0 ; i < G[x].size(); ++i) {

		int node = G[x][i].first;
		int cost = G[x][i].second;

		if(viz[node] == 0 || (node == 1 && deep == N) ) {

			viz[node] = 1;
			dfs(node, deep + 1, sum + cost);
		
			if(node != 1)
				viz[node] = 0;
		}
	}
}


int main() {

	read();
	viz[1] = 1;
	s[++s[0]] = 1;
	dfs(1, 1, 0);
	if(min_sum == (1<<29))
		fout << "Nu exista solutie";
	else
		fout << min_sum << '\n';
	return 0;
}