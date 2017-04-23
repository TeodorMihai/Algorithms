#include <fstream>
#include <vector>
#include <algorithm>


std::ifstream fin("apm.in");
std::ofstream fout("apm.out");

const int NMAX = 200001;
const int MMAX = 400001;

int N; int M; 

int conex[NMAX]; int R[NMAX];


class Edge {

public:

	int x; int y; int cost;

	Edge(int x, int y, int cost) {

		this->x = x;
		this->y = y;
		this->cost = cost;
	}

	Edge() {}

} E[MMAX];

std::vector<Edge> Tree;


bool compare(Edge A, Edge B) {

 	return A.cost < B.cost;
}


void read() {

	fin >> N >> M;

	for(int i = 1; i <= M; ++i) {

		int x; int y; int cost;
		fin >> x >> y >> cost;

		E[i].x = x; E[i].y = y; E[i].cost = cost;
	
	}

}


void unite(int x, int y) {

	if(R[x] > R[y])
		conex[y] = x;
	else conex[x] = y;

	if(R[x] == R[y])
		R[y]++;
}

int find(int x) {

	return (conex[x] == x) ? x : (conex[x] = find(conex[x]));

}

int kruskal() {

	int cost = 0;

	for(int i = 1; i <= N; ++i)
		conex[i] = i, R[i] = 1;

	std::sort(E + 1, E + M + 1, compare);

	for(int i = 1, j = 1; i <= M, j < N; ++i) {

		if(find( E[i].x ) != find( E[i].y ) ) {

			unite( find(E[i].x) , find(E[i].y) );
			Tree.push_back(E[i]);
			cost += E[i].cost;
			++j;
		}
	}

	return cost;
}

int main() {

	read();

	fout << kruskal() << '\n'; 

	fout << N - 1 << '\n';

	for(unsigned i = 0 ; i < Tree.size(); ++i)
		fout <<Tree[i].x << " " <<Tree[i].y << '\n';


	return 0;

}