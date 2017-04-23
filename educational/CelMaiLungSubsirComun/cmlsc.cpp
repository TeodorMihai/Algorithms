#include <bits/stdc++.h>

using namespace std;

ifstream fin("cmlsc.in");
ofstream fout("cmlsc.out");

const int NMAX = (1<<10);

int N; int M;

int A[NMAX];
int B[NMAX];

int sub[NMAX][NMAX]; // sub[i][j] = cmlsc pentru primele i caractere din A si primele j caracetre din B
int ret[NMAX][NMAX];


vector<int> sol;

int find(int x, int y) {

	if(sub[x][y] != -1) 
		return sub[x][y];
	

	if(x == 0 || y == 0)
		return 0;

	int maximum = 0;

	if(A[x] == B[y]) { 

		int val = find(x - 1, y - 1);
		if(maximum < val + 1) {

			maximum = val + 1;
			ret[x][y] = 2;
		}
	}

	int val = find(x - 1, y);

	if(maximum < val) {

		maximum = val;
		ret[x][y] = 1;
	}

	val = find(x, y - 1);

	if(maximum < val) {

		maximum = val;
		ret[x][y] = 0;
	}

	sub[x][y] = maximum;

	return maximum;
}


int main() {

	fin >> N >> M;

	for(int i = 1 ; i <= N; ++i)
		fin >> A[i];

	for(int i = 1 ; i <= M; ++i)
		fin >> B[i];

	for(int i = 1 ; i <= N; ++i)
		for(int j = 1; j <= M; ++j)
			sub[i][j] = -1;

	fout <<	find(N, M) << '\n'; 

	while(N != 0 && M != 0) {

		switch(ret[N][M]) {

			case 2: sol.push_back(A[N]); N--; M--; break;
			case 1: --N; break;
			case 0: --M; break;
		}
	}

	for(int  i = sol.size() - 1 ; i >= 0 ; --i)
		fout << sol[i] << " ";

	return 0;
}