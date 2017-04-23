//casutele de unu sunt muchii, linii sunt nodurile 
//din stanga, coloane nodurile din dreapta => graf bipartit > vertez cover

#include <bits/stdc++.h>

using namespace std;

ifstream fin("paznici.in");
ofstream fout("paznici.out");

const int NMAX = 27;

int n; int m;

int nodesLeft; int nodesRight;

vector<int> g[NMAX];

char s[NMAX - 1][NMAX - 1];

bool used[NMAX];
bool used2[NMAX];

int pairL[NMAX]; int pairR[NMAX];

bool zleft[NMAX];//noduri care sunt unmatched (din stanga)
	//sau care sunt pe un lant alternat de muchii neluate-luate
	//incepand de la nodurile unmatched
bool zright[NMAX];

void read() {

	fin >> n >> m;
	for(int i = 0; i < n; ++i)
		fin >> s[i];
}

void constructGraph() {

	nodesLeft = n;
	nodesRight = m;

	for(int i = 0; i < n ; ++i)
		for(int j = 0; j < m; ++j)
			if(s[i][j] == '1')
				g[i + 1].push_back(j + 1);
}

bool dfs(int node) {

	if(used[node] == true) return false;

	used[node] = true;

	for(int x : g[node])
		if(pairR[x] == 0) {
			pairR[x] = node;
			pairL[node] = x;
			return true;
		}

	for(int x : g[node]) 
		if(dfs(pairR[x])) {
			pairR[x] = node;
			pairL[node] = x;
			return true;
		}

	return false;
}

void cuplaj() {

	memset(used, 0, sizeof(used));

	for(int i = 1; i <= nodesLeft; ++i)
		if(pairL[i] == 0) 
			if(dfs(i) == false) {
				memset(used, 0, sizeof(used));
				dfs(i);
			}
}

void dfsVertexCover(int node, bool pos) {

	if(pos == true) { //right
		
		zright[node] = true;
		used2[node] = true;

		if(pairR[node] != 0 && used[pairR[node]] == false)
			dfsVertexCover(pairR[node], !pos);
	}
	

	if(pos == false) { //left

		used[node] = true;
		zleft[node] = true;

		for(int x : g[node])
			if(used2[x] == false && pairL[node] != x)
				dfsVertexCover(x, true);
	}
}

void vertexCover() {

	memset(used, 0, sizeof(used)); //left
	memset(used2, 0, sizeof(used2)); //right

	for(int i = 1; i <= nodesLeft; ++i)
		if(pairL[i] == 0) 
			dfsVertexCover(i, false);
		
}

void solve() {

	constructGraph();
	cuplaj();
	vertexCover();
}

void print() {

	for(int i = 1; i <= nodesLeft; ++i)
		if(zleft[i] == false)
			fout << (char) (i  + 'A' - 1);

	for(int i = 1; i <= nodesRight; ++i)
		if(zright[i] == true)
			fout << (char) (i + 'a' - 1);

	fout << '\n'; 
}

int main() {

	read();
	solve();
	print();
	return 0;
}