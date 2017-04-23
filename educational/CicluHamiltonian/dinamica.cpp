#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>

using namespace std;


ifstream fin ("hamilton.in");
ofstream fout ("hamilton.out");

const int NMAX = 18;
const int MAX_CONF = (1 << NMAX);
const int INF = (1<<29);

int N;  int M;

vector<int> G[NMAX];

int D[MAX_CONF][NMAX]; //costul minim de a ajunge de la nodul 0 ( ales de noi) pana la nodul NMAX, trecand prin toate nodurile i cu (1 << i) & MAX_CONF = 1

int min_sum = INF;

int C[NMAX][NMAX];

void read() {


	fin >> N >> M; 

	for(int i = 1; i <= M; ++i)  {

		int x; int y; int cost;
		fin >> x >> y >> cost;
		G[y].push_back(x);
		C[x][y] = cost;

	}

}


int calc(int start, int conf, int last) {

	if(D[conf][last] == -1) {

		D[conf][last] = INF;

		for(unsigned i = 0 ; i < G[last].size(); ++i)
			if((1 << G[last][i]) & conf) {

				if(start == G[last][i]  && ( ( (1 << last) ^ conf) != (1 << start) ) ) continue ;//nu vreau sa trec de 2 ori pin nodul start,
				//decat daca configuratia noastra consta doar din nodul de start si nodul last, practic astfel intializez 
				//configuratiile cudoar 2 noduri cu costul muchiei intre ele

				D[conf][last] = min(D[conf][last], calc(start, conf ^ (1 << last), G[last][i] ) + C[ G[last][i] ][ last ] );
			}
	}

	return D[conf][last];
}

void solve() {

	int conf = (1 << N);
	memset(D, -1, sizeof(D));
	
	for(int i = 0 ; i < N; ++i)
		D[(1 << i)][i] = 0; //costul minim de ajunge de la nodul i la el insusi, adica 0
		
	for(unsigned j = 0; j < G[0].size(); ++j)
		min_sum = min(min_sum, calc(0, conf - 1, G[0][j]) + C[ G[0][j] ][ 0 ]);
	
	
	
}


int main() {

	read();
	

	solve();


	if(min_sum == INF)
		fout << "Nu exista solutie";
	else
		fout << min_sum << '\n';

	return 0;
}