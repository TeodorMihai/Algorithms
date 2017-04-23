#include <bits/stdc++.h>

using namespace std;

const int NMAX = 105;

ofstream fout("plimbare.in");

int main()  {

	srand(time(NULL));

	int n = rand() % 100 + 1;
	int m = n * (n - 1) / 2;

	fout << n << '\n'; 

	for(int i = 1; i <= n ; ++i)
		for(int j = i + 1; j <= n ; ++j) {

			int orient = rand() % 2;

			if(j >= n/2)
				orient = 1;

			if(orient == 0)
				fout << i << ' ' << j << '\n';
			else 
				fout << j << ' ' << i << '\n';
		}

	return 0;
}