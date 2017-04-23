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

void solve() {

	int conf = (1 << N);
	memset(D, -1, sizeof(D));

	int start = 0;

	for(int i = 0 ; i < conf; ++i)
		for(int j = 0 ; j < N; ++j)
			D[i][j] = INF;

	D[1][0] = 0;
	
	for(int i = 0 ; i < conf; ++i) { //pun mai intai for-ul asta si nu cel cu last pentru ca altfel 
		// D[i][j] ar insemna la momentu j = x, toate drumurile minime cu primele j noduri,
		//iar pentru last = N - 1 ar insemna ca toate drumurile de N elemente se vor termina doar in last, last neputand fi bagat la mijloc
	
		for(int last = 0 ; last < N; ++last) {	
			if(i & ( 1<< last))

				for(unsigned j = 0 ; j < G[last].size(); ++j) {

					int inter = G[last][j];

					if ( ( 1 << inter ) & i)  { //trebuie ca conf sa contina nodul intermediar, si pe last

						//if(start == inter && ( ( ( 1 << start ) ^ conf) != ( 1 << last ) ) ) continue; 
						//nu mai avem nevoie de asta pentruc ca nodul start nu mai poate aparea ca intermediar
						
						D[i][last] = min(D[i][last], D[i ^ ( 1 << last )][ inter ] + C[ inter ][last] ); 


					}
				}
		}
	}

	
}


int main() {

	read();
	

	solve();

	for(unsigned i = 0 ;i < G[0].size(); ++i)
		min_sum = min(min_sum, D[(1 << N) - 1][ G[0][i] ] + C[ G[0][i] ][0]	);

	if(min_sum == INF)
		fout << "Nu exista solutie";
	else
		fout << min_sum << '\n';

	return 0;
}

//compexitate: O(N * 2 ^ N)