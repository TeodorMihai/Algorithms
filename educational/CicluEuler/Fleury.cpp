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

int check[NMAX];

vector<pair2> E;
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
		E.push_back(mp(x, y));
	}
}

bool check_euler() {

	for(int i = 1; i <= N; ++i)
		if(In[i] % 2 !=  0)
			return 0;
	return 1;
}


void DFS(int x) {

	check[x] = 1;

	for(unsigned i = 0 ; i < G[x].size(); ++i)
		if(check[ G[x][i].first ] == 0) {

			viz[ G[x][i].second ] = 1;//muchie care face parte din arbore, nu e muchie de intoarcere 
			DFS(G[x][i].first);
		}
}

void mark_edges() {


	DFS(1);
}


void go(int x) {

//1-muchie din arbore, 0 - mchie de intoarere, 2 - muchie scoasa
//mergem mai intai pe muchiile de intoarcere, alea cu 0
	int ret = -1; int ok = 0; int ret_node = -1;

	for(unsigned i = 0 ; i < G[x].size(); ++i) {
		
		int edge = G[x][i].second;
		int node = G[x][i].first;
		
		if( viz[edge] == 2 ) continue;

		if( viz[edge] == 0) {

			cycle.push_back(edge);
			viz[edge] = 2;
			ok = 1;
			go(node);
			return ;


		}

		if(viz[edge] == 1) {
			ret = edge;
			ret_node = node;
		}

	}

	if(ret != -1 && ok == 0) {
		cycle.push_back(ret);
		viz[ret] = 2;
		go(ret_node);
	}

}

void make_cycle() {

	go(1);
}

int main() {

	read();

	if(!check_euler()) {
		fout << -1;
		return 0;
	}


	mark_edges();

	//for(unsigned i = 0 ; i < M ; ++i)
	//	fout << viz[i] <<" ";

	make_cycle();

	int last = 1; //ultimul nod ca sa afisam in ordine

	//fout << last << " ";

	for(unsigned i = 0; i < cycle.size(); ++i) 
		if( E[cycle[i]].first == last ) {
			fout << E[cycle[i]].second << " ";
			last = E[cycle[i]].second;
		}
		else  {
			last = E[cycle[i]].first;
			fout << E[cycle[i]].first <<  " ";
		}
	return 0;
}