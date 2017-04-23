#include <fstream>
#include <algorithm>


std::ifstream fin("disjoint.in");
std::ofstream fout("disjoint.out");

const int NMAX = 100001;

int N; int M; 

int T[NMAX]; int R[NMAX];

void unite(int x, int y) {

	if(R[x] > R[y]) {

		T[y] = x;
		R[y] = std::max(R[y], R[x] + 1);

	} else {

		T[x] = y;
		R[x] = std::max(R[x], R[y] + 1);
	}
}

int find(int x) {

	return (T[x] == x) ? x : (T[x] = find(T[x]));
}


void solve() {

	fin >> N >> M;

	for(int i = 1; i <= N; ++i) {

		R[i] = 1;
		T[i] = i;
	}

	for(int i = 1; i <= M; ++i) {

		int x; int y; int type;

		fin >> type >> x >> y;

		switch(type) {

			case 2: 
				if( find(x) == find(y) ) 
					fout << "DA" << '\n';
				else 
					fout << "NU" << '\n';
			break; 

			case 1: 

				unite(find(x), find(y));

			break;
		}
	}
}

int main() {

	

	solve();


	return 0;


}