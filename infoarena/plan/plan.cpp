#include <bits/stdc++.h>

using namespace std;

ifstream fin("plan.in");
ofstream fout("plan.out");

const int NMAX = 260;

#define pp pair<int,int>

int n; int m;

vector<int> g[NMAX];
vector<int> gt[NMAX];

int viz[NMAX];

int ord[NMAX];

int ctc[NMAX]; int cnt;

vector<int> gctc[NMAX];

int inctc[NMAX];

int xset[NMAX];
int yset[NMAX];
int taken[NMAX];
vector<int> ctcnodes;

vector<pp> edges;

vector<int> in0;
vector<int> out0;

int resolved[NMAX];

void read() {

	fin >> n >> m;
	for(int  i = 1; i <= m ; ++i) {
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

void dfsCtc(int node, int repr) {

	viz[node] = 1;
	ctc[node] = repr;

	for(int x : gt[node])
		if(viz[x] == 0)
			dfsCtc(x, repr);
}

void dfsSet(int node, int start) {

	viz[node] = 1;

	for(int x : gctc[node]) {

		if(taken[x] == 0 && taken[start] == 0 && gctc[x].size() == 0) {
			taken[x] = 1;
			taken[start] = 1;
			xset[++xset[0]] = start;
			yset[++yset[0]] = x;
			return ;
			//am dum start -> x
		}

		if(viz[node] == 0)
			dfsSet(x, start);
	}
}

void solve() {

	//scot comp tare conexe, kosaraju
	for(int i = 1; i <= n ; ++i)
		if(viz[i] == 0)
			dfs(i);

	memset(viz, 0, sizeof(viz));

	for(int i = ord[0] ; i > 0 ; --i)
		if(viz[ord[i]] == 0) {
			dfsCtc(ord[i], ord[i]);
			ctcnodes.push_back(ord[i]);
		}

	//construiesc dag-ul ctc-urilor
	for(int i = 1; i <= n ; ++i)
		for(int x : g[i]) 
			if(ctc[x] != ctc[i])  {
				gctc[ctc[i]].push_back(ctc[x]);
				inctc[ctc[x]]++;
			}

	//construiesc mulimea maximala (x1, y1) , (x2, y2), (x3, y3)...(xk, yk)
	memset(taken, 0, sizeof(taken));
	for(int x : ctcnodes) {
		
		if(inctc[x] == 0)
			in0.push_back(x);

		if(gctc[x].size() == 0)
			out0.push_back(x);

		if(inctc[x] == 0)  {
			memset(viz, 0, sizeof(viz));
			dfsSet(x, x);
		}	
	}	

	if(ctcnodes.size() == 1) {
		fout << 0 << '\n'; 
		return ;
		//graful e deja tare conex
	}
	//Pot ajunge : (x1, y1) (x2, y2)...
	//Duc (y1, x2), (y2, x3) , (y3, x1) => creez ciclul
	for(int i = 1; i <= xset[0] - 1; ++i) {
		resolved[yset[i]] = resolved[ xset[i + 1] ] = 1;
		edges.push_back({yset[i], xset[i + 1]});
	}
	if(xset[0] > 0) {
		resolved[yset[ yset[0] ]] = resolved[ xset[1] ] = 1;
		edges.push_back({yset[ yset[0] ], xset[1]});
	}
	//alea care au mai ramas in multimi le duc intre ele, o sa se anexeze la ciclu
	for(int x : in0)
		for(int y : out0)
			if(resolved[x] == 0 && resolved[y] == 0) {
				edges.push_back({y, x});
				resolved[x] = resolved[y] = 1;
			}
	//au mai ramas noduri doar intr-o multime(in0 sau out0), le anexam si pe ele la ciclu
	for(int x : in0)
		if(resolved[x] == 0)
			edges.push_back({out0[0], x});

	for(int y : out0)
		if(resolved[y] == 0)
			edges.push_back( {y, in0[0]} );

	fout << edges.size() << '\n'; 

	for(pp p : edges)
		fout << p.first << ' ' << p.second << '\n'; 
		
}

int main() {

	read();
	solve();
	return 0;
}