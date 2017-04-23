#include <bits/stdc++.h>

using namespace std;

ifstream fin("strmatch.in");
ofstream fout("strmatch.out");

const int NMAX = 2e6 + 5;

int n; int m;
char a[NMAX]; char b[NMAX];
int pii[NMAX];
vector<int> sol;

// pii[i] = lungimea celui mai lung prefix al sirului a[1..i] 
//care coincide cu sufixul sau, dar diferit de a[1..i]

int main() {

	fin >> a + 1; n = strlen(a + 1);
	fin >> b + 1; m = strlen(b + 1);

	pii[1] = 0;
	int pos = 0;

	for(int i = 2 ; i <= n; ++i) {
		
		while(pos > 0 && a[pos + 1] != a[i])
			pos = pii[pos];

		if(a[i] == a[pos + 1])
			pos++;
		pii[i] = pos;

	}

	//for(int i = 1; i <= n; ++i)
	//	cout << pii[i] << '\n'; 

	sol.reserve(1000);
	int cnt = 0;
	pos = 0;

	for(int i = 1; i <= m; ++i) {

		while(pos > 0 && b[i] != a[pos + 1])
			pos = pii[pos];
		
		if(b[i] == a[pos + 1])
			pos++;

		if(pos == n) {
		
			cnt++;

		 	if(sol.size() < 1000)
				sol.push_back(i - n);
		}
	}

	fout << cnt << '\n';

	for(int x : sol)
		fout << x << ' ';
	
	return 0;
}