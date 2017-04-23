#include <bits/stdc++.h>

using namespace std;

ifstream fin("lapte.in");
ofstream fout("lapte.out");

const int NMAX = 104;

#define pp pair<int,int>
#define x first
#define y second

const int INF = 0x3f3f3f3f;

int n; int l;
pp v[NMAX];

int d[NMAX][NMAX]; int last[NMAX][NMAX][2];
//d[i][j] = nr maxim de litri de lapte B bauti stiind ca sau baut j litri 
//de lapte A pana la omul i

int check(int x) {
	//x = timpul avut la dispozitie

	for(int i = 0; i <= n ; ++i) {
		for(int j = 0 ; j <= l ; ++j)
			d[i][j] = -INF;
		d[i][0] = 0;
	}


	for(int i = 1; i <= n; ++i) 
		for(int baut1 = 0 ; baut1 <= x / v[i].x ; ++baut1) {
			
			int baut2 = (x - baut1 * v[i].x) / v[i].y;

			for(int j = l ; j  >= baut1 ; --j) {

				if(d[i][j] <= d[i - 1][j - baut1] + baut2)  {
					d[i][j] = d[i - 1][j - baut1] + baut2;

					last[i][j][0] = baut1;
					last[i][j][1] = baut2;
				}
			}
		}

	if(d[n][l] >= l)
		return 1;

	return 0;
}

void print(int i, int baut,int t) {

	if(i == 0)
		return;
	print(i - 1, baut - last[i][baut][0], t);
	fout << last[i][baut][0] << ' ' << last[i][baut][1] << '\n';
}

int bs() {

	int step, pos ;

	for(step = 1 ; step <= 10000 ; step <<= 1);

	for(pos = 0 ; step ; step >>= 1)
		if(pos + step <= 10000 && check(pos + step) == 0)
			pos += step;
	return pos + 1;
}

int main() {

	fin >> n >> l;
	
	for(int i = 1; i <= n ; ++i)
		fin >> v[i].x >> v[i].y;
	int t = bs();

	fout << t << '\n';
	check(t);
	print(n, l, t);

	return 0;
}