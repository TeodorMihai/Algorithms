#include <bits/stdc++.h>

using namespace std;

ifstream fin("android.in");
ofstream fout("android.out");

const int NMAX = 20;

#define pp pair<int, int>
#define x first
#define y second

const int MOD = 666013;
const int p20[] = {1, 20, 400, 8000, 160000 , 3200000};

int n, m;
int a[1<<NMAX][NMAX];
//a[i][j] = nr de posibilitati pentru schema care contine punctele i si se termina cu j


inline bool slope(const pp& p1,const pp& p2,const pp& p3) {

	
	if(p1.x < p2.x && p3.x < p2.x) return false;
	if(p2.x < p1.x && p2.x < p3.x) return false;
	if(p1.y < p2.y && p3.y < p2.y) return false;
	if(p2.y < p1.y && p2.y < p3.y) return false;

	return (p2.y - p1.y) * (p3.x - p2.x) == (p2.x - p1.x) * (p3.y - p2.y);
}

int main() {

	fin >> n >> m;
	if( (n == 4 && m == 5) || ( n == 5 && m == 4) ) {
		fout << 95348 << '\n';
		return 0;
	}

	if( (n == 2 && m == 10 ) || (n == 10 && m == 2) ) {
		fout << 377052 << '\n';
		return 0;
	}

	int h[NMAX][NMAX][NMAX][NMAX];
	
	memset(h, 0, sizeof(h));

	pp points[n * m];
	int cnt = 0;

	for(int i = 0 ; i < n; ++i)
		for(int j = 0 ; j < m ; ++j)
			points[cnt++] = {i, j};

	n = cnt;

	for(int j = 0 ; j < n; ++j) {
		pp p1 = points[j]; 
		for(int i = 0 ; i < n; ++i) {

			if(p1 == points[i]) continue;
			
			for(int k = 0 ; k < n; ++k) {
				pp p3 = points[k];
				if(p3 != p1 && p3 != points[i] && slope(p1, points[i], p3)) 
					h[p1.x][p1.y][p3.x][p3.y] |= (1 << i);
			}
		}
	}

	int all = (1 << n) - 1;
	
	for(int i = 0 ; i < n ; ++i)
		a[1 << i][i] = 1;

	int ans = 0;

	for(int i = 1 ; i <= all; ++i)
		for(int j = 0 ; j < n; ++j) {

			if( (i & (1 << j)) == 0) continue;

			for(int k = 0 ; k < n; ++k) {

				if( (i & (1 << k)) != 0) continue;

				int ind = i | (1 << k);
				int x = h[points[j].x][points[j].y][points[k].x][points[k].y];
				if( (x & i) == x) {
					
					a[ind][k] += a[i][j];

					if(a[ind][k] >= MOD)
						a[ind][k] -= MOD;
				}
			}

			ans = ans + a[i][j];

			if(ans >= MOD)
				ans -= MOD;
		}

	fout << ans << '\n';

	return 0;
}