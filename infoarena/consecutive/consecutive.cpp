//Daca trebuie sa incerci, incearca tot timpul pe o variabile care variaza
//cel mai putin, variabile respectiva nu trebuie neaparat sa fie definita propiu
//zis in problema
#include <bits/stdc++.h>

using namespace std;

ifstream fin("consecutive.in");
ofstream fout("consecutive.out");

#define pp pair<int,int>

long long n; 

vector<pp> sol;

void solve() {

	for(long long dif = 2; dif * (dif + 1)  <= n * 2; dif++) {
		// x (x + 1)  - y (y + 1) = n * 2
		// x ^ 2 + x - y ^ 2 - y = n * 2
		// (x + y) * (x - y) + x - y = n * 2=>
		// s * dif + dif = n * 2 => s = (2 * n - dif) / dif 
		//=> x = (s + dif) / 2 , y = s - x

		if( (2 * n - dif) % dif == 0) {
			long long s = (2 * n - dif) / dif;

			if( (s + dif) % 2 == 0) {
				int x = (s + dif) / 2;
				int y = s - x;
				sol.push_back({y, x});
			}
		}
	}

	fout << sol.size() << '\n'; 

	for(pp p : sol)
		fout << p.first + 1 << ' ' << p.second << '\n';
}

int main() {

	int t;
	fin >> t;

	while(t--) {

		fin >> n;
		solve();
		sol.clear();
	}
}