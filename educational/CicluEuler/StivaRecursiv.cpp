#include <fstream>
#include <vector>

using namespace std;


ifstream fin ("ciclueuler.in");
ofstream fout ("ciclueuler.out");


const int NMAX = 100001;
const int MMAX = 500001;

#define pair2 pair<int,int>
#define mp make_pair


int N; int M;

int viz[MMAX];

vector<pair2> G[NMAX];
vector<int> cycle;

int In[NMAX];

void read() {

	fin >> N >> M;

	for(int i = 1; i <= M; ++i) {

		int x; int y;
		fin >> x >> y;

		G[x].push_back(mp(y, i - 1));
		G[y].push_back(mp(x, i - 1));
		In[x]++;
		In[y]++;
	}
}

bool check_euler() {

	for(int i = 1; i <= N; ++i)
		if(In[i] % 2 !=  0)
			return 0;
	return 1;
}


void euler(int x) {

	for(unsigned i = 0; i < G[x].size(); ++i) {

		int node = G[x][i].first;
		int edge = G[x][i].second;

		if(viz[edge] == 0) {

			viz[edge] = 1;
			euler(node);
		}

	}	
	//cand un nod nu mai are vecini insemna ca am terminat un ciclu
	//acum ori ma intorc si incep sa bag noduri care formeaza un alt ciclu(dar care se termina obligatoriu cu nodul pe care tocmai l.am bagat si care a inceput ciclul)
	//ori inchid acest si ma intorc pana ajung sa bag din nou acest nod x	
	cycle.push_back(x);
}

int main() {

	read();

	if(!check_euler()) {
		fout << -1;
		return 0;
	}

	euler(1);

	for(unsigned i = 0 ; i < cycle.size() - 1; ++i)
		fout << cycle[i] << " ";


	return 0;
}