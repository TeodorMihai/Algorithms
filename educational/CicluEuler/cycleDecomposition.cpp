#include <bits/stdc++.h>

using namespace std;

ifstream fin("ciclueuler.in");
ofstream fout("ciclueuler.out");

#define pp pair<int,int>

const int NMAX = 100009;
const int MMAX = 500009;
/*din cauza ca fac parcurgere pe muchii (pot trece prin acelasi nod de 2 ori)
=> pot sparge stiva => h max stiva = MMAX fata de NMAX clasic*/

int n; int m;

vector<pp> g[NMAX];

int degree[NMAX];

int viz[NMAX];

vector<int> cycle;

void read() {

	fin >> n >> m;

	for(int i = 1; i <= m ; ++i) {
		int x; int y;
		fin >> x >> y;
		g[x].push_back({y, i});
		g[y].push_back({x, i});
		degree[x]++; degree[y]++;
	}
}

void euler(int node) {

	for(pp edge : g[node])
		if(viz[edge.second] == 0) 
			viz[edge.second] = 1, euler(edge.first);

	cycle.push_back(node);
	//Propietate pt care chestia asta e corecta:
	//Intr-un graf eulerian(conex si cu gr fiecarui nod % 2 == 0, 
	//nodul in care ma blochez va fi ADIACENT cu nodul de unde am inceput parcurgerea)
	//De ce? Pentru ca nodurile din care incep si in care termin sunt 
	//singurele care au gradul impar (consderand ca am sters muchiile deja vizitate) 
	//nu ma pot bloca decat cand dau peste un cu gradul impar, daca e par am unde sa ma duc

	//Practic merg e un ciclu, incep sa bag muchii in el, daca dau peste alt ciclu 
	//adiacent continui cu el (dar nu bag imediat muchiile), ci incep sa le bag
	//dupa ce am terminat si cu acest ciclu adiacent
}

void solve() {

	for(int i = 1; i <= n ; ++i)
		if(degree[i] % 2) {
			fout << -1 << '\n';
			return ;
		}

	euler(1);

	for(int x : cycle)
		fout << x << ' ';
	fout << '\n'; 

}

int main() {

	read();
	solve();

	return 0;
}