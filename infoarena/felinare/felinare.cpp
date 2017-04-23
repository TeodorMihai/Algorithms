//independenet set and vertez cover set are complementar

#include <bits/stdc++.h>

using namespace std;

ifstream fin("felinare.in");
ofstream fout("felinare.out");

const int NMAX = 9000;

int n; int m;

int nodesLeft; int nodesRight;

vector<int> g[NMAX];

bool used[NMAX];
bool used2[NMAX];

int pairL[NMAX]; int pairR[NMAX];

bool zleft[NMAX];//noduri care sunt unmatched (din stanga)
	//sau care sunt pe un lant alternat de muchii neluate-luate
	//incepand de la nodurile unmatched
bool zright[NMAX];

int c;

vector<int> left;
vector<int> right;

void read() {

	fin >> n >> m;

	nodesLeft = nodesRight = n;

	for(int i = 1; i <= m; ++i) {
		int x; int y;
		fin >> x >> y;
		//felinar1 -> felinar2
		g[x].push_back(y);
	}
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
				c += dfs(i);
			} else 
				c++;
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

	cuplaj();
	vertexCover();
}

void print() {

	int nrFelinare = 0;
	//independent set:

	for(int i = 1; i <= n; ++i)
		if(zleft[i] == true && zright[i] == false)
			 nrFelinare += 2;
		else if(zleft[i] == false && zright[i] == true)
			nrFelinare = nrFelinare;
		else if(zleft[i] == true && zright[i] == true)
			nrFelinare++;
		else 
			nrFelinare++;

	fout << nrFelinare << '\n';

	for(int i = 1; i <= n; ++i)
		if(zleft[i] == true && zright[i] == false)
			fout << 3 << '\n';
		else if(zleft[i] == false && zright[i] == true)
			fout << 0 << '\n'; 
		else if(zleft[i] == true && zright[i] == true)
			fout << 1 << '\n';
		else 
			fout << 2 << '\n';

	fout << '\n'; 
}

int main() {

	read();
	solve();
	print();
	return 0;
}