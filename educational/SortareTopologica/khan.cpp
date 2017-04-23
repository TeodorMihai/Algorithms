#include <bits/stdc++.h>

using namespace std;

ifstream fin("sortaret.in");
ofstream fout("sortaret.out");

const int NMAX = 50009;

int n; int m;

vector<int> g[NMAX];
queue<int> q;
vector<int> top;

int in[NMAX];

void read() {

	fin >> n >> m;
	for(int  i = 1; i <= m; ++i) {
		int x; int y;
		fin >> x >> y;
		g[x].push_back(y);
		in[y]++;

	}
}

void solve() {

	for(int i = 1 ; i <= n; ++i)
		if(in[i] == 0)
			q.push(i);

	while(q.empty() == false) {

		int node = q.front();
		q.pop();
		top.push_back(node);

		for(auto x : g[node]) {

			in[x]--;

			if(in[x] == 0)
				q.push(x);
		}
	}
}

void print() {

	for(auto x : top)
		fout << x << ' ';
}



int main() {

	read();

	solve();

	print();

	return 0;
}