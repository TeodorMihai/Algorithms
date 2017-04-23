#include <bits/stdc++.h>

using namespace std;

ifstream fin("car.in");
ofstream fout("car.out");

const int NMAX = 505;
const int dx[] = {0, -1, -1, -1, 0, 1, 1, 1};
const int dy[] = {1, 1, 0, -1, -1, -1, 0, 1};

int n, m;
int a[NMAX][NMAX];
int sx, sy, fx, fy;


vector<int> dist[2];

bool visited[1 << 21];

void read() {


	fin >> n >> m;
	fin >> sx >> sy >> fx >> fy;
	sx--;
	sy--;
	fx--;
	fy--;

	for(int i = 0 ; i < n ; ++i)
		for(int j = 0 ; j < m ; ++j)
			fin >> a[i][j];
}


int getV(int x, int y, int dir) {
	return (((x << 9) + y) << 3) + dir;
}

int getX(int value) {
	return (value >> 12) & 511;
}

int getY(int value) {
	return (value >> 3) & 511;
}

int getDir(int value) {

	return value & 7;
}


void expand(int cost, int value) {

	int x = getX(value);
	int y = getY(value);
	int dir = getDir(value);

	//intorc 45 grade pastrez pozitia, cost 1
	
	int vec1 = getV(x, y, (dir + 1) & 7);
	if(visited[vec1] == false)
		dist[(cost + 1) & 1].push_back(vec1);
	
	int vec2 = getV(x, y, (8 + dir - 1) & 7);

	if(visited[vec2] == false)
		dist[(cost + 1) & 1].push_back(vec2);



	//cost 0, pastrez directia
	if(x + dx[dir] >= 0 && y + dy[dir] >= 0 && x + dx[dir] < n && y + dy[dir] < m && 
		a[x + dx[dir]][y + dy[dir]] == 0) {

		int vec3 = getV(x + dx[dir], y + dy[dir], dir);

		if(visited[vec3] == false)
			dist[cost & 1].push_back(vec3);
	}

}

void solve() {

	int cost = 0;

	for(int i = 0 ; i < 8 ; ++i) 
		dist[0].push_back(getV(sx, sy, i));

	while(dist[0].size() + dist[1].size() > 0) {

		while(dist[ cost & 1 ].size() > 0) {

			int x = dist[cost & 1][dist[cost & 1].size() - 1];
			dist[cost & 1].pop_back();
			expand(cost, x);

			visited[x] = true;
			
			if(getX(x) == fx && getY(x) == fy) {
				fout << cost << '\n';
				return ;
			}
		}

		cost++;
	}

	fout << -1 << '\n';

}

int main() {

	read(); solve();

	return 0;
}