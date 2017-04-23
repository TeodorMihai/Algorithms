#include <bits/stdc++.h>

using namespace std;

ifstream fin("calandrinon.in");
ofstream fout("calandrinon.out");

const int NMAX = 1000005;

int n;

char s[NMAX];

int f[200]; int nr;

int g[200];

int start = -1;

bool can(int x) {

	for(char c = 'a' ; c <= 'z' ; ++c)
		if(g[c] == f[c] && f[c] > 0)
			return 0;
	return 1;
}

int main() {

	fin >> n;
	fin >> s;

	for(int i = 0 ; i < n ; ++i)
		f[s[i]]++;

	for(char c = 'a' ; c <= 'z' ; ++c)
		if(f[c])
			nr++;

	
	int cnt = 0;

	for(int j = 0 ; j < nr; ++j) {

		int next = -1;

		for(char c = 'a' ; c <= 'z'; ++c)
			g[c] = 0;

		for(int i = start + 1; i < n ; ++i)
			if(f[s[i]] > 0) {
				g[s[i]]++;
				if(next == -1 ||  s[next] > s[i]  )
					next = i;
				if(f[s[i]]  - g[s[i]] == 0) 
					break;
				
			}
		fout << s[next];


		for(int i = start + 1; i <= next; ++i)
			f[s[i]]--;

		f[s[next]] = 0;
		start = next;
	}


	return 0;
}	