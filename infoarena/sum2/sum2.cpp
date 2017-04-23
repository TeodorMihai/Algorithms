#include <bits/stdc++.h>

using namespace std;

ifstream fin("sum2.in");
ofstream fout("sum2.out");

#define pp pair<int, int>
#define x first
#define y second

const int NMAX = 1e5 + 5;

int n; int l, u; int b = -0x3f3f3f3f;

int a[NMAX], s[NMAX];
deque<pp> q;

int main() {

	fin >> n >> l >> u;

	for(int i = 1; i <= n; ++i)
		fin >> a[i], s[i] = s[i - 1] + a[i];

	//j1 < j2 , a[j1] > a[j2], j1 poate fi eliminat

	if(l == n) {
		fout << s[n] << '\n';
		exit(0);
	}
 
	q.push_front({0, 0});

	for(int i = l + 1; i <= n ; ++i) {

		while(q.empty() == false && q.back().first >= s[i - l])
			q.pop_back();

		q.push_back({s[i - l], i - l});

		if(q.empty() == false && i - q.front().second > u) 
			q.pop_front();

		if(s[i] - q.front().first > b)
			b = s[i] - q.front().first;
	}

	fout << b << '\n';

	return 0;
}
