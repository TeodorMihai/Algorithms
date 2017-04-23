#include <bits/stdc++.h>

using namespace std;

ifstream fin("triunghi.in");
ofstream fout("triunghi.out");

const int NMAX = 1e6 + 5;

int n, s;
bool mark[NMAX];
int prev1[NMAX], used[500];

vector<int> nr;

int ans[20][20];
int inf[20][20];

int main() {

	fin >> n >> s;

	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= i; ++j)
			inf[i][j] = inf[i - 1][j - 1] + inf[i - 1][j] + 1;
	
	int sum = 0;

	for(int i = 1; i <= n ; ++i) {
		if( i <= n - i + 1) 
			nr.push_back(inf[n][i]);
		sum += inf[n][i];
	}

	if(sum > s) {
		fout << "imposibil\n";
		return 0;
	}

	for(int i = 0 ; i < nr.size(); ++i)
		used[nr[i]]++;

	mark[sum] = true;

	for(int x : nr) 
		for(int i = 0; i <= s - x; ++i)
			if(mark[i]) {
				mark[i + x] = mark[i];
				prev1[i + x] = x;
			}

	if(mark[s] == false) {
		fout << "imposibil\n";
		return 0;
	}

	while(s != sum) {

		used[prev1[s]]++;
		s -= prev1[s];
	}

	for(int i = 0 ; i < nr.size(); ++i)
		ans[0][i] = used[nr[i]];

	for(int i = nr.size(); i < n ; ++i)
		ans[0][i] = 1;

	for(int i = 1; i < n; ++i)
		for(int j = 0; j < n - i; j++)
			ans[i][j] = ans[i - 1][j] + ans[i - 1][j + 1];

	for(int i = 0; i < n ; ++i) {
		for(int j = 0; j <= i ; ++j)
			fout << ans[n - i - 1][j] << ' ';
		fout << '\n';
	}



	return 0;
}