#include <bits/stdc++.h>

using namespace std;

ifstream fin("traseu.in");
ofstream fout("traseu.out");

const int NMAX = 62;
const int INF = 0x3f3f3f3f;

int n; int m;

int cost[NMAX][NMAX];

void read() {

	fin >> n >> m;
	for(int i = 1; i <= m ; ++i) {
		int x; int y;
		fin >> x >> y;
	}
	
}
int main() {

	read(); solve();
	return 0;

}