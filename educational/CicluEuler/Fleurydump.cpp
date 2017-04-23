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

	for(unsigned i = 0; i < G[x].size(); ++i)
		if(check[G[x][i].first] == 0)
			DFS(G[x][i].first);

}

bool is_isolated(int x) {


	for(unsigned i = 0 ; i < G[x].size(); ++i)
		if(viz[ G[x][i].second ] == 0)
			return false;
	return true;
}

bool is_conex(int x) {

	for(unsigned i = 1 ; i <= N; ++i)
		check[i] = 0;

	for(int i = 1; i <= N; ++i) {
		for(unsigned j = 0 ; j < G[i].size(); ++i)
			if(viz[ G[i][j].second ]  == 0 ) { //daca nu e izolat incep dfs-UL din el
				DFS(G[i][j].first);
				i = N + 1;
				break;
			}
	}

	for(int i = 1 ; i <= N; ++i)
		if(check[i] == 0 && !is_isolated(i))
			return false;
	for(unsigned i = 0 ; i < G[x].size(); ++i)
		if(viz[G[x][i].second] == 0)
			return true;
	return false;

}

void go(int x) {

//1-muchie din arbore, 0 - mchie de intoarere, 2 - muchie scoasa
//mergem mai intai pe muchiile de intoarcere, alea cu 0
	

	for(unsigned i = 0 ; i < G[x].size(); ++i) {
		
		int node = G[x][i].first;
		int edge = G[x][i].second;

		if(viz[edge] == 0) {

			viz[edge] = 1;
			//o scot din graf
			if(!is_conex(node)) 
				viz[edge] = 0;
			
			else  {
				cycle.push_back(edge);
				go(node);
			}


		}	
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



	//for(unsigned i = 0 ; i < M ; ++i)
	//	fout << viz[i] <<" ";

	make_cycle();
	for(unsigned i = 0 ; i < M; ++i)
		if(viz[i] == 0)
			cycle.push_back(i);
	int last = 1; //ultimul nod ca sa afisam in ordine

	for(unsigned i = 0; i < cycle.size(); ++i) 	{

		fout << last << " ";
		//fout << cycle[i] <<" ";
		
		if( E[cycle[i]].first == last ) {
			
			last = E[cycle[i]].second;
		}
		else  {
			last = E[cycle[i]].first;
		}
		

	}

	return 0;
}