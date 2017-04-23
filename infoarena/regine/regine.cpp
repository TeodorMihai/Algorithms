#include <bits/stdc++.h>

using namespace std;

ifstream fin("regine.in");
ofstream fout("regine.out");

int n;

int main() {

	fin >> n;
	int q = (2 * n + 1) / 3;
	fout << q << '\n';

	if(n % 3 == 1) {

		int p = (n + 1) / 2;
		int c1 = ((2 * n + 1) / 3 + 1) / 2;
		int c2 = ((4 * n + 2) / 3 + 1) / 2;
		int cnt = 0;
		int cnt2 = 0;
		int j = 0;
		for(int i = n ; i >= n - q + 1; --i, cnt++, j++) {
			if(j % 2 == 0 && i != n)
				cnt2++;
			if(cnt % 2 == 0)
				fout << i << ' ' << c1 - cnt2 << '\n';
			else 
				fout << i << ' ' << c2 - cnt2 << '\n';
		
		}
	} else {

		int p = (n + 1) / 2;

		int c1 = ((2 * n + 1) / 3 + 1) / 2;
		int c2 = ((4 * n + 2) / 3 + 2) / 2;
		int cnt = (n % 3 == 0) ? 1 : 0;
		int start = ( n % 3 == 0 ) ? n : n  ;

		int cnt2 = 0;
		int j = 0;
		for(int i = start; i >= start - q + 1; --i, cnt++, ++j) {
			if(j % 2 == 0 && i != start)
				cnt2++;
			if(cnt % 2 == 0)
				fout << i << ' ' << c1 - cnt2 << '\n';
			else 
				fout << i << ' ' << c2 - cnt2 << '\n';
			
		}
	}

	return 0;
}