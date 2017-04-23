#include <bits/stdc++.h>

using namespace std;

ifstream fin("plimbare.in");
ofstream fout("plimbare.out");

const int NMAX = 108;

int n; int m;

bool edge[NMAX][NMAX];

vector<int> g[NMAX];
vector<int> gt[NMAX];

int ord[NMAX]; bool viz[NMAX];

int repr[NMAX]; int cnt[NMAX];

vector<int> cycle;

bool circuitFound;

vector<int> s[5];

//s[0] = toate nodurile din com tare conexa cu nr maxim de noduri
//s[1] = noduri din circuit(in ordine)
//s[2] = noduri care au arce si spre circuit, si arce din cirucit spre ele
//s[3] = noduri cu arce doar spre cirucit
//s[4] = noduri cu arce doar dinspre circuit spre ele

//Intr-o ctc orice nod se afla in una dintre aceste multimi (este graf turneu)

void read() {

	fin >> n ;
	
	m = n * (n - 1) / 2;

	for(int i = 1; i <= m ;++i) {
		int x; int y;
		fin >> x >> y;
		edge[x][y] = true;	
		g[x].push_back(y);	
		gt[y].push_back(x);
	}
}

void dfs(int nod) {

	viz[nod] = 1;

	for(int x : g[nod])
		if(viz[x] == false)
			dfs(x);

	ord[++ord[0]] = nod;
}

void kosaraju(int nod, int repres) {

	viz[nod] = true;
	repr[nod] = repres;
	cnt[repres]++;

	for(int x : gt[nod])
		if(viz[x] == false)
			kosaraju(x, repres);
}

void findCircuit(int nod) {

	viz[nod] = true;

	if(circuitFound == false)
		cycle.push_back(nod);

	for(int x : g[nod]) {

		if(repr[nod] != repr[x]) continue;
	
		if(viz[x] == false)
			findCircuit(x);
		else if(circuitFound == false) {

			circuitFound = true;
			s[1].push_back(x);
			for(int i = cycle.size() - 1; i >= 0; --i)
				if(cycle[i] == x)
					break;
				else 
					s[1].push_back(cycle[i]);
			s[1].push_back(x);
			reverse(s[1].begin(), s[1].end());
		}
	}
}

void constructSets() {

	//s[1] e ok restul nu neaparat, trebuiesc actualizate
	memset(viz, 0, sizeof(viz));

	for(int x : s[1])
		viz[x] = true;

	for(int i = 2; i <= 4; ++i)
		s[i].clear();

	for(int x : s[0]) {

		if(viz[x] == true) continue; //deja face parte din circuit

		bool edgeIn = false;//x -> circuit
		bool edgeOut = false;//circuit -> x

		for(int y : g[x])
			if(repr[y] == repr[x])
				if(viz[y] == true)
					edgeIn = true;

		for(int y : gt[x])
			if(repr[y] == repr[x])
				if(viz[y] == true)
					edgeOut = true;	
		
		if(edgeIn && edgeOut)
			s[2].push_back(x);
		else if(edgeIn && !edgeOut)
			s[3].push_back(x);
		else if(!edgeIn && edgeOut)
			s[4].push_back(x);
	}
}

void hamiltonCircuit(int nod) { //in graf turneu

	for(int i = 1; i <= n; ++i)
		if(repr[i] == nod)
			s[0].push_back(i);

	memset(viz, 0, sizeof(viz));

	findCircuit(nod);//gaseste un circuit oarecare
	//s[1].push_back(s[1][0]); //sa am ciclu complet
	constructSets();

	//ct timp nu am gasit circuitul hamilton
	while(s[1].size() - 1 < cnt[ repr[ s[1][0] ] ]) {

		//inserez toate nodurile din s[2]
		while(s[2].size() > 0) {

			int x = s[2][0];
			
			for(int i = 1 ; i < s[1].size(); ++i)//rup un arc din circuit ca sa-mi bag nodul
				if(edge[ s[1][i - 1] ][x] && edge[x][ s[1][i] ]) {
					s[1].insert(s[1].begin() + i , x);
					viz[x] = true;
					break;
				}

			constructSets();
		}


		//circuit -> s[4]
		//s[4] -> s[3] ,altel nu ar fi graf turneu si nu ar fi comp tare conexa
		//s[3] -> cirucit
		//circuit -> s[4] -> s[3] -> cirucit
		
		while(s[3].size() > 0 && s[4].size() > 0) {

			int s4 = s[4][0];
			int s3 = 0;
			//gasim un nod din s3 ai s4 -> y (s3)
			for(int y : s[3])
				if(edge[s4][y] && repr[s4] == repr[y]) {
					s3 = y;
					break;
				}

			for(int i = 1 ; i < s[1].size(); ++i) {
				int cir1 = s[1][i - 1];
				int cir2 = s[1][i];
				if(edge[cir1][s4] && edge[s4][s3] && edge[s3][cir2])  {

					s[1].insert(s[1].begin() + i, s4);
					s[1].insert(s[1].begin() + i + 1, s3);
					viz[s3] = viz[s4] = true;
					break;
				}
			}

			constructSets();
			if(s[2].size() > 0) break;

		}
	}


}

void solve() {

	for(int i = 1; i <= n; ++i)
		if(viz[i] == false)
			dfs(i);

	memset(viz, 0, sizeof(viz));

	for(int i = ord[0] ; i ; i--)
		if(viz[ord[i]] == false) 
			kosaraju(ord[i], ord[i]);
	
	memset(viz, 0, sizeof(viz));
	int maxComp = 0;
	
	for(int i = 1; i <= n; ++i)
		if(cnt[repr[i]] > cnt[maxComp])
			maxComp = repr[i];

	hamiltonCircuit(maxComp);

	fout << s[1].size() - 1 << '\n'; 
	for(int i = 0 ; i < s[1].size() - 1; ++i)
		fout << s[1][i] << ' ';
		
}

int main() {

	read();
	solve();
	return 0;
}