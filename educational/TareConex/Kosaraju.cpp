#include <fstream>
#include <vector>

using namespace std;

ifstream fin ("ctc.in");
ofstream fout ("ctc.out");

const int NMAX = 100001;

int N; int M;

int viz[NMAX];

int S[NMAX];

vector<int> G[NMAX]; vector<int> Gt[NMAX];

vector< vector<int> > ctc;

vector<int> cc;

void read() {

	fin >> N >> M;

	for(int i = 1; i <= M; ++i) {

		int x; int y;
		fin >> x >> y;

		G[x].push_back(y);
		Gt[y].push_back(x);
	}
}


void DFS(int x) {

	viz[x] = 1;

	for(unsigned i = 0 ;i < G[x].size(); ++i)
		if(viz[G[x][i]] == 0)
			DFS(G[x][i]);
	
	S[++S[0]] = x;
}


void DFSTranspus(int x) {

	viz[x] = 0;
	cc.push_back(x);

	for(unsigned i = 0 ; i < Gt[x].size(); ++i)
		if(viz[ Gt[x][i] ] == 1)
			DFSTranspus(Gt[x][i]);
}

void kosaraju() {

	/*
	Practic faci o sorare topologica mai intai, in primul nod din sortarea topologica nu poti ajunge din alt nod(decat daca cele 2 
	sunt intr.un ciclu, cea ce insemna ca sunt si intr.o componenta conexa)
	*/

	for(int i = 1; i <= N; ++i) {

		if(viz[i] == 0)
			DFS(i);
	}

	for(int i = S[0]; i > 0 ; --i) {

		if(viz[S[i]] == 1) {

			cc.clear();

			DFSTranspus(S[i]);
			ctc.push_back(cc);
		}
	}
}


int main() {


	read();

	kosaraju();

	fout << ctc.size() << '\n';

	for(unsigned i = 0 ; i < ctc.size() ; ++i) {
		for(unsigned j = 0 ; j < ctc[i].size(); ++j)
			fout << ctc[i][j] << " ";
	
		fout << '\n';
	}


	return 0;
}