//KTarjan O(n +  m)
#include <bits/stdc++.h>

using namespace std;

ifstream fin("ctc.in");
ofstream fout("ctc.out");

const int NMAX = 100009;

int n; int m;

vector<int> g[NMAX];

vector< vector<int> > ctc; int cnt;

int viz[NMAX];
int s[NMAX];
int low[NMAX];
int discovery;
int ins[NMAX];
int ind[NMAX];

void read() {

	fin >> n >> m;
	for(int i = 1; i <= m ; ++i) {
		int x; int y;
		fin >> x >> y;
		g[x].push_back(y);
	}
}

void tarjan(int node) {

	viz[node] = 1;
	++discovery; 
	ind[node] = discovery;//punctul de descoperire
	low[node] = discovery;//cat de sus putem ajunge de la nodul x

	s[++s[0]] = node;//bag nodul pe stiva
	ins[node] = 1;

	for(int x : g[node]) 
		if(viz[x] == 0) {
			tarjan(x);
			low[node] = min(low[node], low[x]);
		} else if(ins[x] == 1) 
			low[node] = min(low[node], low[x]);
			//a fost vizitat si a ramas in stiva, daca nu ar fi fost in stiva	
			//ar fi insemnat ca sigur e din alta componenta tare conexa
			//ale carei noduri au fost vizitate complet (asta insemna ca nu se poate
			//ajunge dintr-un nod de-al ei la nodul meu node, ci doar din node la x)

	if(low[node] == ind[node]) { //niciun nod din subarborele ramas al lui node
								 //nu are un alt drum in sus peste nodul node => o noua ctc	
		ctc.push_back(vector<int>(0));
		int x;
		do {
			ins[ s[s[0]] ] = 0;
			ctc[cnt].push_back( (x = s[s[0]]) );
			s[0]--;
		} while(node != x);
		cnt++;
	}
	
}

void solve() {

	for(int i = 1; i <= n; ++i)
		if(viz[i] == 0)
			tarjan(i);
	fout << cnt << '\n'; 

	for(int i = 0 ; i < cnt; ++i) {
		for(int x : ctc[i])
			fout << x << ' ';
		fout << '\n'; 
	}
}

int main() {

	read(); solve();

	return 0;
}