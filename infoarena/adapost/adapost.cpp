#include <bits/stdc++.h>

using namespace std;

ifstream fin("adapost.in");
ofstream fout("adapost.out");

#define pp pair<double, double>

const int NMAX = 404;
const double eps = 0.001;
const double MAXD = 1500;
const double INF = 1e7;

int n; int s; int d;

double cost[NMAX][NMAX];

pp lefty[NMAX];
pp righty[NMAX];

bool viz[NMAX];
int pairL[NMAX];
int pairR[NMAX];

int rez[NMAX * 2][NMAX * 2];
double cost2[NMAX * 2][NMAX * 2];
int ant[NMAX * 2];

vector<int> g[NMAX * 2];


double dist(pp p1, pp p2) {
	return sqrt((p1.first - p2.first) * (p1.first - p2.first) 
	+ (p1.second - p2.second) * (p1.second - p2.second));
}

void read() {

	fin >> n;

	for(int i = 1; i <= n; ++i) 
		fin >> lefty[i].first >> lefty[i].second;

	for(int i = 1; i <= n; ++i) {

		fin >> righty[i].first >> righty[i].second;

		for(int j = 1; j <= n; ++j) 
			cost[j][i] = dist(lefty[j], righty[i]);
		
	}
}

bool dfs(int node, double maxDistance) {

	if(viz[node] == true) return false;

	viz[node] = true;

	for(int i = 1; i <= n ; ++i)
		if(maxDistance >= cost[node][i] && pairR[i] == 0) {
			pairR[i] = node;
			pairL[node] = i;
			return true;
		}

	for(int i = 1; i <= n; ++i) 
		if(maxDistance >= cost[node][i] && dfs(pairR[i], maxDistance) == true) {
			pairR[i] = node;
			pairL[node] = i;
			return true;
		}
	return false;
}

int cuplaj(double maxDistance) { //O(sqrt(N) * M)

	int c = 0;
	memset(pairL, 0, sizeof(pairL));
	memset(pairR, 0, sizeof(pairR));

	for(bool go = true; go ; ) {

		go = false;
		memset(viz, 0, sizeof(viz));

		for(int i = 1; i <= n; ++i)
			if(pairL[i] == 0 && dfs(i, maxDistance)) 				
				c++, go = true;
			
	}

	return c;
}

double modulo(double x) {
	return x > 0 ? x : -x;
}

bool bf(int s, int d, double maxDistance) {

	bool inq[NMAX * 2];
	double dis[NMAX * 2];
	queue<int> q;

	memset(inq, 0, sizeof(inq));
	for(int i = s; i <= d; ++i)
		dis[i] = INF;

	dis[s] = 0;
	q.push(s);
	inq[s] = true;
	ant[d] = 0;

	for( ; q.empty() == false ; q.pop() ) {
		int node = q.front();
		inq[node] = false;

		for(int i : g[node])
			if(rez[node][i] > 0 && dis[i] >= dis[node] + cost2[node][i]) {

				dis[i] = dis[node] + cost2[node][i];
				ant[i] = node;
				
				if(inq[i] == false) 
					q.push(i);
				inq[i] = true;
			}
	}

	return ant[d] != 0;

}

double cuplajCostMinim(double maxDistance) { //O(N^2 * M)

	s = 0;
	d = 2 * n + 1;
	double costMinim = 0;

	for(int i = 1; i <= n; ++i) {
		g[s].push_back(i);
		g[i].push_back(s);

		g[i + n].push_back(d);
		g[d].push_back(i + n);

		cost2[s][i] = 0; cost2[i + n][d] = 0;
		rez[s][i] = 1;
		rez[i + n][d] = 1;
	}

	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j) {
			cost2[i][j + n] = cost[i][j];
			cost2[j + n][i] = -cost[i][j];
			
			if(cost[i][j] <= maxDistance) {
				g[i].push_back(j + n);
				g[j + n].push_back(i);
				rez[i][j + n] = 1;
			}
		}

	while( bf(s, d, maxDistance) ) {

		int maxFlow = 1;

		for(int x = d; x != s; x = ant[x]) {
			rez[ant[x]][x] -= 1;
			rez[x][ant[x]] += 1;
			costMinim += cost2[ant[x]][x];
		}
	} 

	return costMinim;
}

void solve() {


	double pos ; double step = MAXD;

	for(pos = 0; step > 1e-7; step /= 2)
		if(pos + step <= MAXD && cuplaj(pos + step) < n)
			pos += step;

	fout << fixed << setprecision(10) << pos + 1e-6  << ' ';
	fout << fixed << setprecision(10) << cuplajCostMinim(pos + 1e-5) << '\n'; 
}

int main() {

	read(); solve();

	return 0;

}