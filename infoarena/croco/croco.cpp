#include <bits/stdc++.h>

using namespace std;

ifstream fin("croco.in");
ofstream fout("croco.out");

const int NMAX = 112;
const int INF = 0x3f3f3f3f;

int n; int s; int d;

int ant[NMAX];
int rez[NMAX][NMAX];//cat mai pot sa pompez din nodul i in nodul j
int croc[NMAX][NMAX];
int mark[NMAX];

void read() {

	fin >> n;

	for(int i = 1; i <= n ; ++i) 
		for(int j = 1; j <= n; ++j)
			fin >> rez[i][j], croc[i][j] = rez[i][j];
}


bool bfs(int s, int d) {

	bool viz[NMAX];
	queue<int> q;
	memset(viz, 0, sizeof(viz));
	
	q.push(s);
	viz[s] = true;
	mark[s] = true;

	while(q.empty() == false) {

		int node = q.front();
		q.pop();

		for(int i = 1 ; i <= n; ++i)
			if(viz[i] == false && rez[node][i] > 0) {
				ant[i] = node;
				viz[i] = true;
				mark[i] = true;
				q.push(i);
			}
	}

	return viz[d];
}

int solve() {

	while( bfs(s, d) == true) {

		for(int i = 1; i <= n; ++i) {

			int maxFlow = rez[i][d];

			if(maxFlow <= 0) continue;

			for(int x = i; x != s; x = ant[x])
				maxFlow = min(maxFlow, rez[ant[x]][x]);

			rez[i][d] -= maxFlow;
			rez[d][i] += maxFlow;

			for(int x = i; x != s ; x = ant[x]) {
				rez[ant[x]][x] -= maxFlow;
				rez[x][ant[x]] += maxFlow;
			}
		}
	}


	memset(mark, 0, sizeof(mark));
	bfs(s, d);//gasesc taietura minima

	int croco = 0;

	for(int i = 1; i <= n; ++i)
		for(int j = 1; j < i; ++j)
			if(mark[i] == mark[j])
				croco += croc[i][j];


	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			rez[i][j] = croc[i][j];

	return croco;
}


void print() {

	int cnt = 0;

	for(int i = 1; i <= n; ++i)
		if(mark[i] == true)
			cnt++;

	int croco = 0;

	for(int i = 1; i <= n; ++i)
		for(int j = 1; j < i; ++j)
			if(mark[i] == mark[j])
				croco += croc[i][j];

	fout << croco << ' ' << cnt << '\n';

	for(int i = 1; i <= n; ++i)
		if(mark[i] == true)
			fout << i << ' ';

	fout << '\n'; 
}

int main() {

	read(); 

	s = 1;
	int maxInd = 2;
	int maxSum = 0;

	for(int i = 2; i <= n; ++i) {
		
		d = i;
		int cr = solve();

		if(cr > maxSum) {
			maxInd = i;
			maxSum = cr;
		}
	}

	d = maxInd;

	solve();
	print();

	return 0;
}