#include <bits/stdc++.h>

using namespace std;

ifstream fin("palmieri.in");
ofstream fout("palmieri.out");

#define point pair<int,int>
#define x first
#define y second

const int NMAX = 25e4 + 5;

int n; long long a;

point v[NMAX];

struct cmp {

	bool operator()(point p1, point p2) {
		if(p1.x == p2.x)
			return p1.y > p2.y;
		return p1.x < p2.x;
	}
} cmpU;

int main() {

	fin >> n >> a;

	for(int i = 1; i <= n ; ++i) 
		fin >> v[i].x >> v[i].y;

	sort(v + 1, v + 1 + n, cmpU);

	int cnt = 0;

	//for(int i = 1; i  <= n; ++i)
	//	fout << v[i].x << ' ' << v[i].y << '\n';

	for(int i = 1; i <= n ;) {

		int h = 0;
		int dif = 0;
		int j = i ;
		for( ;  j <= n && 1ll * h * dif <= a; j++ ){
			h = max(h, v[j].y);
			dif = v[j].x - v[i].x;
		}

		cnt++;
		if(j > n){
			if(1ll * h * dif > a)
				cnt++;
		 	break;
		}
		--j;
		i = j;
	}

	fout << cnt << '\n';

	return 0;
}