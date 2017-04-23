#include <fstream>

#include <vector>


using namespace std;

ifstream fin("sortaret.in");
ofstream fout("sortaret.out");

const int NMAX = 50001;
const int MMAX = 100001;


int N; int M;

vector<int> G[NMAX];

vector<int> V;

int viz[NMAX];

void read() {

	fin >> N >> M;

	while(M--) {

		int x; int y;
		fin >> x >> y;
		G[x].push_back(y);

	}
}

void DFS(int x) {

	viz[x] = 1;

	for(unsigned i = 0 ; i < G[x].size(); ++i) {

		if(viz[G[x][i]] == 1) continue;

		DFS(G[x][i]);

	}

	V.push_back(x);

}

int main() {

	read();

	for(int i = 1; i <= N; ++i)
		if(viz[i] == 0)
			DFS(i);

	for(int i = V.size() - 1 ; i >= 0; --i)
		fout << V[i] << " ";

	return 0;
}