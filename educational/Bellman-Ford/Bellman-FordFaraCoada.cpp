#include <fstream>
#include <vector>
#include <queue>

std::ifstream fin ("bellmanford.in");
std::ofstream fout("bellmanford.out");

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

bool BellmanFord(int start) {

	for(int i = 1; i <= N; ++i)
		dist[i] = INF;

	dist[start] = 0;

	for(int i = 0 ; i <  N - 1; ++i) {

		//luam fiecare muchie de N - 1. Daca a N-a vreo muchie mai imbunatateste ceva insemna ca avem un ciclu de cost negativ
		for(int j = 1; j <= N; ++j) {

			for(unsigned k = 0 ; k < G[j].size(); ++k) {
				
				//imbunatatim ceva daca se poate

				int node = G[j][k].first;
				int cost = G[j][k].second;

				if(dist[node] > dist[j] + cost) 

					dist[node] = dist[j] + cost;
				

			}
		}
	}

	for(int i = 1; i <= N; ++i)
		for(unsigned j = 0 ;j < G[i].size() ; ++j)
			if(dist[G[i][j].first] > dist[i] + G[i][j].second)	
				return 0;
	return 1;

}

int main() {

	read();

	if(BellmanFord(1)) 
		for(int i = 2; i <= N; ++i)
			fout << dist[i] << " ";
	else fout << "Ciclu negativ!" << '\n';

	return 0;
}

//complexitate: O(V * (logV + E)), simplificat pentru grafuri conexe: O(E * log V)
//Dijkstra nu merge pt muchii negative pentru ca nu se repsecta propietatea de minim, intodeauna la un nod s.ar putea sa se ajunga prin altfel 
//cu un cost mai mic folosind o muchie negativa