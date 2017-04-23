#include <bits/stdc++.h>

using namespace std;

ifstream fin("cuplaj.in");
ofstream fout("cuplaj.out");
	
const int NMAX = 1e5 + 9;

int nodesLeft; int nodesRight; int m;

int pairL[NMAX];
int pairR[NMAX];

vector<int> g[NMAX];

bool used[NMAX];
int cuplaj;

void read() {

	fin >> nodesLeft >> nodesRight >> m;

	for(int i = 1; i <= m ; ++i) {
		int x; int y;
		fin >> x >> y;
		g[x].push_back(y);
	}
}


bool dfs(int node) {

	//practic dfs pentru a cauta un nod liber
	// liber <=> pairR[x] == 0, marchez nodurile folosite
	//corespondenta e 1:1 pentru nodurile vizitate asa ca nu trebuie
	//sa marchez si nodurile din stanga si cele din dreapta,
	//le marchez doar pe cele din stanga

	if(used[node] == true) return false;

	used[node] = true;

	for(int x : g[node])
		if(pairR[x] == 0) {
			pairR[x] = node;
			pairL[node] = x;
			return true;
		}

	for(int x : g[node]) 
		if(dfs(pairR[x])) {//parcurg 2 arce deodata, unul e de "inoarcere"
			pairR[x] = node;
			pairL[node] = x;
			return true;
		}

	return false;
}

void solve() {

	for(int i = 1; i <= nodesLeft; ++i)
		if(pairL[i] == 0) {
			//prefer sa nu resetez nodurile de fiecare data
			//practic daca fac dfs intr-un arbore (din noduri random) cautand iesiri 
			//aka noduri de pe un nivel ultim, prefer sa las noduri
			//marcate ca interzise (deja vizitate), e o mare sansa ca acele noduri sa
			//duca spre regiuni blocate (fara noduri libere), euristic e mai eficient
			//dar nu e neaparat o optimizare
			if(dfs(i))
				cuplaj++;
			else {
				memset(used, 0, sizeof(used));
				cuplaj += dfs(i);
			}
		}
}

void print() {

	fout << cuplaj << '\n';

	for(int i = 1; i <= nodesLeft; ++i)
		if(pairL[i])
			fout << i << ' ' << pairL[i] << '\n';
}

int main() {

	read(); solve(); print();

	return 0;
}