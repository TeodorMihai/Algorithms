//Kosaraju O (n + m)

//se face o sortare topologica pe graful a reprezentatnilor COMPONENTELOR TARE CONEXE care e un dag
//se parcurge dintr-un nod in a carui componenta tare conexa nu intra nimic pe graful normal,
//pe graful transpus, orice nod care e atins face parte din respectiva componenta tare conexa
// (pentru ca daca plec din nodul x, pot ajunge in oricare alt nod y =>x -> y, datorita 
//soratrii topologice, daca din nodul x merg pe graful transpus si ajung la y, insemna ca pe graful 
//normal din y pot ajunge in x => x si y in aceeasi componenta tare conexa.

#include <bits/stdc++.h>

using namespace std;

ifstream fin("ctc.in");
ofstream fout("ctc.out");

const int NMAX = 100009;

int n; int m;

vector<int> g[NMAX];
vector<int> gt[NMAX];

vector< vector<int> > ctc; int cnt;

int ord[NMAX];
int viz[NMAX];

void read() {

	fin >> n >> m;
	for(int i = 1; i <= m ; ++i) {
		int x; int y;
		fin >> x >> y;
		g[x].push_back(y);
		gt[y].push_back(x);
	}
}

void dfs(int node) {

	viz[node] = 1;
	for(int x : g[node])
		if(viz[x] == 0)
			dfs(x);
	ord[++ord[0]] = node;
}

void dfsT(int node, int cnt) {

	ctc[cnt].push_back(node);
	viz[node] = 1;

	for(int x : gt[node])
		if(viz[x] == 0)
			dfsT(x, cnt);
}

void solve() {

	for(int i = 1; i <= n; ++i)
		if(viz[i] == 0)
			dfs(i);

	memset(viz, 0, sizeof(viz));

	for(int i = ord[0]; i > 0 ; --i)
		if(viz[ ord[i] ] == 0) {
			ctc.push_back(vector<int>(0));
			dfsT(ord[i], cnt);
			cnt++;
		}
	
	fout << cnt << '\n'; 

	for(int i = 0 ; i < cnt; ++i) {
		for(int j = 0 ; j < ctc[i].size() ; ++j)
			fout << ctc[i][j] << ' ';
		fout << '\n'; 
	}

}

int main() {

	read(); solve();

	return 0;
}