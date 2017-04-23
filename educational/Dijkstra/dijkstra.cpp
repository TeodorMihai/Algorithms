#include <fstream>
#include <vector>
#include <queue>

std::ifstream fin ("dijkstra.in");
std::ofstream fout("dijkstra.out");

const int NMAX = 50001;
const int MMAX = 250000;
const int INF = (1<<30);

int N; int M; int dist[NMAX];

std::vector< std::pair<int, int> > G[NMAX];

void read() {

	fin >> N >> M;

	int x; int y; int cost; 

	for(int i = 0 ;i < M; ++i) {

		fin >> x >> y >> cost;

		G[x].push_back(std::make_pair(y, cost));

	}
}

int* Dijkstra(int start) {

	int *dist = new int[NMAX];

	int state[NMAX]; // 0 - out, 1 - in queue, 2 - untouched


	std::priority_queue< std::pair<int, int> , std::vector< std::pair <int, int> > , std::greater<std::pair < int, int > > > Q;
	//by default priority queue ia cea mai amre valoare
	//std::priority_queue < std::pair < int, int > > Q;

	Q.push(std::make_pair(0, start));

	for(int i = 1 ; i <= N; ++i) {
		dist[i] = INF;
		state[i] = 2; //nevizitat
	}

	state[start] = 1; //in queue
	dist[start] = 0;

	while(!Q.empty()) {

		int P = Q.top().second;
		Q.pop();

		for(unsigned i = 0 ; i < G[P].size(); ++i) {

			int node = G[P][i].first;
			int cost = G[P][i].second;


			if(state[node] == 0) continue; //deja vizitat, nu ne itnoarcem inapoi nu am imbunatati nimic probabil, though nu e gresit

			if(dist[node] > dist[P] + cost) {

				dist[node] = dist[P] + cost;

				Q.push(std::make_pair( dist[node], node) );

				state[node] = 1; //in queue;

			}	
		}

		state[P] = 0; //am terminat cu nodul
	}

	return dist;
}

int main() {

	read();

	int *dist = Dijkstra(1);

	for(int i = 2 ; i <= N; ++i )
		if(dist[i] == INF)
			fout << 0 << " ";
		else fout << dist[i] << " ";

	return 0;
}

//complexitate: O(V * (logV + E)), simplificat pentru grafuri conexe: O(E * log V)