#include <fstream>
#include <vector> 
#include <queue>

std::ifstream fin("apm.in");
std::ofstream fout("apm.out");


const int NMAX = 200001;
const int MMAX = 400000;
const int INF = (1<<30);

#define pair2 std::pair<int, int>
#define pair3 std::pair<int, std::pair<int, int> >
#define mp std::make_pair

int N; int M;

std::vector< pair2 > G[NMAX];

std::vector < pair2 > Tree;


void read() {

	fin >> N >> M;

	for(int i = 1; i <= M; ++i) {

		int x; int y; int cost;
		fin >> x >> y >> cost;
		G[x].push_back(std::make_pair(y, cost));
		G[y].push_back(std::make_pair(x, cost));
	}
}

int Prim() {

	std::priority_queue < pair3 , std::vector < pair3 > , std::greater < pair3 > > Q;

	int distance[NMAX];

	int cost = 0;

	int start = 1;  int viz[NMAX]; int i;

	for(int i = 1; i <= N; ++i)
		viz[i] = 0, distance[i] = INF;

	viz[start] = 1; distance[start] = 0;

	for(unsigned i = 0 ; i < G[start].size(); ++i) {

		Q.push(mp(G[start][i].second,mp( G[start][i].first, start ) ) );
	
		distance[ G[start][i].first ] = G[start][i].second;
	
	}

	while(i < N - 1) {

		int node = Q.top().second.first;
		int node_tree = Q.top().second.second;

		int ad_cost = Q.top().first;

		Q.pop();

		if(viz[node] == 1) continue;

		Tree.push_back(mp(node,node_tree ));

		cost = cost + ad_cost;
		++i;

		for(unsigned j = 0 ;j < G[node].size(); ++j) {

			if(viz [ G[node][j].first ] == 1) continue;

			if(distance[G[node][j].first] > G[node][j].second ) {

				Q.push(mp( G[node][j].second,mp( G[node][j].first, node) ) );
				distance[ G[node][j].first ] = G[node][j].second;
			}

		}

		viz[node] = 1;
	}

	return cost;
}

int main() {

	read();

	fout << Prim() << '\n';

	fout << N - 1 << '\n'; 

	for(int i = 0 ; i < N - 1; ++i)
		fout << Tree[i].first << " " << Tree[i].second << '\n';

	return 0;


}