#include <bits/stdc++.h>

using namespace std;

ifstream fin("base3.in");
ofstream fout("base3.out");

const int NMAX = 16005;
const int INF = 0x3f3f3f3f;

int dist[NMAX * 4 + 100];

#define dist (dist + 2 * NMAX)
#define pp pair<int, int>

char s[3][NMAX * 2]; int len[3];

void read() {

	fin >> s[0] >> s[1] >> s[2];
	for(int i = 0 ; i < 3; ++i) len[i] = strlen(s[i]);
}

void solve() {

	int inf = -NMAX * 2;
	int sup = NMAX * 2;

	for(int i = inf; i <= sup; ++i)
		dist[i] = INF;

	priority_queue<pp, vector<pp> , greater<pp> > pq;

	for(int i = 0 ; i < 3; ++i)
		for(int j = 0 ; j < len[i]; ++j)
			if(s[i][j] == '1') {
				int node = j - (len[i] - j - 1);				
				//cate in dreapta - cate in stanga
				dist[ node ] = len[i];
				pq.push({dist[node], node});
			}

	while(pq.empty() == false) {

		int node = pq.top().second;
		int d = pq.top().first;

		if(node == 0) {
			fout << dist[node] << '\n';
			return ;
		}

		pq.pop();

		for(int i = 0 ; i < 3; ++i) {
			//dreapta
			int newD = d + len[i];
			int newNode = node - len[i];

			if(newNode <= sup && newNode >= inf && dist[newNode] > newD) {
				dist[newNode] = newD;
				pq.push({newD, newNode});
			}
			//stanga
			newNode = node + len[i];

			if(newNode <= sup && newNode >= inf && dist[newNode] > newD) {
				dist[newNode] = newD;
				pq.push({newD, newNode});
			}
		}
	}

	fout << 0 << '\n'; 

}

int main() {

	read();

	solve();

	return 0;
}