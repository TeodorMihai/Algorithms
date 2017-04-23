#include <bits/stdc++.h>

using namespace std;

ifstream fin("biti.in");
ofstream fout("biti.out");

#define pp pair<int, int>

const int NMAX = 19;

int n; 

vector<pp> g[1 << NMAX];
stack<int> s;
int viz[ (1<<20) + 30];
char st[ (1<<20) + 40]; int m;

int main() {

	fin >> n;


	m = (1 << n) + n - 1;
	fout << (1 << n) + n - 1 << '\n';
	if(n == 1) {
		fout << "01\n";
		return 0;
	}
	int last = (1 << (n - 1))  - 1;
	int cnt = 0;

	for(int i = 0 ; i <= last; ++i) {

		int node0 = (i << 1) & last;
		int node1 = ((i << 1) & last) + 1;
		g[i].push_back({node0, ++cnt});
		g[i].push_back({node1, ++cnt});
	}

	st[m] = '\0';
	s.push(0);

	while(s.empty() == false) {

		int node = s.top(); 

		if(g[node].size() == 1 && viz[g[node][0].second] == 0) {
			viz[g[node][0].second] = 1;
			s.push(g[node][0].first);
			continue;
		} else {

			if(viz[ g[node][0].second ] == 0) {
				viz[g[node][0].second] = 1;
				s.push(g[node][0].first);
				continue;
			} else if(viz[ g[node][1].second ] == 0) {
				viz[g[node][1].second] = 1;
				s.push(g[node][1].first);
				continue;
			}
		}
		st[--m] = ( (node & 1) == 0) ? '0' : '1';
		
		s.pop();
	}

	while(m > 0)
		--m, st[m] = '0';
	fout << st << '\n';
	
	fout << '\n';
	
	return 0;
}