#include <bits/stdc++.h>

using namespace std;

ifstream fin("avioane2.in");
ofstream fout("avioane2.out");

const int NMAX = 30009;
const int MMAX = 90009;
const int KMAX = 120009;
const int INF = 0x3f3f3f3f;

struct eveniment {

	int tip; int tm; int aer; int avion; int cost;
	eveniment() { }
	eveniment(int _tip, int _tm, int _aer, int _avion, int _cost) : 
	tip(_tip) , tm(_tm) , aer(_aer), avion(_avion) , cost(_cost) { }
};

vector<eveniment> v;

int n; int m; int k;

int cost[NMAX];
int sol[KMAX];

void read() {

	fin >> n >> m >> k;

	for(int i = 1; i <= m ; ++i) {

		int a; int tdec; int b; int tater; int c;

		fin >> a >> tdec >> b >> tater >> c;

		v.push_back(eveniment(2, tdec, a, i, c));
		v.push_back(eveniment(1, tater, b, i, c));
	}

	for(int i = 1; i <= k ; ++i) {

		int x; int y;
		fin >> x >> y;
		v.push_back(eveniment(3, y, x, i, 0));//avion o sa fie indicele aici
	}

	sort(v.begin(), v.end(), [] (const eveniment& a ,const eveniment& b) -> bool {
		if(a.tm == b.tm)
			return a.tip < b.tip;
		return a.tm < b.tm ;
	}); 

	for(eveniment x : v)
		cout << x.tip << ' ' << x.tm <<  ' ' << x.aer << ' ' << x.avion <<'\n'; 

}

void solve() {

	map<int, int> m;
	// (x , y) = putem ajunge folosind avionul x, cu un cost y, dar inca nu a aterizat
	for(int i = 1; i <= n ; ++i)
		cost[i] = INF;
	
	cost[1] = 0;

	for(eveniment x : v) {

		if(x.tip == 2) { //dcolare

			m[x.avion] = cost[x.aer] + x.cost;
			continue;
		}

		if(x.tip == 1) {

			if(cost[x.aer] > m[x.avion]) 
				cost[x.aer] = m[x.avion];

			m.erase(x.avion);
		}

		if(x.tip == 3) {

			if(cost[x.aer] == INF)
				sol[x.avion] = -1;
			else 
				sol[x.avion] = cost[x.aer];
		}
	}

	for(int i = 1; i <= k; ++i)
		fout << sol[i] << '\n'; 
}

int main() {

	read();
	solve();
	return 0;
}