#include <bits/stdc++.h>

using namespace std;

ifstream fin("petsoft.in");
ofstream fout("petsoft.out");

const int NMAX = 1009;

int n; 

vector<int> g[NMAX];
int d[NMAX][2];
//d[i][0] = maximul pentru subarborele lui daca i e luat , d[i][1] = daca i nu e luat

bitset<NMAX> viz;

int a[NMAX][NMAX];

int mabs(int x) {

	return x < 0 ? -x : x;
}

int dinamica(int st, int dr, vector<int>& v) {

	if(st > dr)
		return 0;

	if(a[v[st]][v[dr]] != 0)
		return a[v[st]][v[dr]];

	if(st == dr) 
		return max(d[v[st]][1], d[v[st]][0]);

	a[v[st]][v[dr]] = d[v[st]][1] + d[v[dr]][1] + mabs(v[st] - v[dr]) + dinamica(st + 1, dr - 1, v);
	a[v[st]][v[dr]] = max(a[v[st]][v[dr]], d[v[st]][0] + dinamica(st + 1, dr, v));
	a[v[st]][v[dr]] = max(a[v[st]][v[dr]], d[v[dr]][0] + dinamica(st, dr - 1, v));

	return a[v[st]][v[dr]];

}

void solve(vector<int> v, int x) {

	sort(v.begin(), v.end());

	for(int i = 0 ; i < (int) v.size(); ++i)
		for(int j = 0 ; j < (int) v.size(); ++j)
			a[v[i]][v[j]] = 0;
	
	int rez = dinamica(0, v.size() - 1, v);
	//x nu e luat, de aia nu apartine vectorului

	vector<int> vp = v;
	vp.push_back(x);
	sort(vp.begin(), vp.end());

	for(int i = 0 ; i < (int)vp.size(); ++i)
		for(int j = 0 ; j < (int)vp.size(); ++j)
			a[vp[i]][vp[j]] = 0;
	
	//0 => x e luat, apartine vectorului
	d[x][0] = dinamica(0, vp.size() - 1, vp);
	d[x][1] = rez;
}

void dfs(int node) {

	viz[node] = 1;

	for(int x : g[node]) {

		if(viz[x] == 0)
			dfs(x);	
	}

	solve(g[node], node);
}


int main() {

	fin >> n ; 

	for(int i = 2; i <= n ; ++i) {

		int x;
		fin >> x;

		g[x].push_back(i);
	}

	dfs(1);

	fout << d[1][1] << '\n';

	return 0;
}