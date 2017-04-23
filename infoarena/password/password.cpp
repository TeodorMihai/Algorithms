#include <bits/stdc++.h>

using namespace std;

ifstream fin("password.in");
ofstream fout("password.out");


const int NMAX = 1e5 + 5;

int n; char s[NMAX];

int main() {

	fin >> s;
	n = strlen(s);

	int p = 1;//pana aici am evaluat exclusiv
	int cand = 0;//cel mai bun candidat din intervalul [0, p - 1]
	int l = 0;

	while(p < n && cand + l < n) {

		if(s[ (p + l) % n] == s[cand + l])  ++l;
		if(s[ (p + l) % n] > s[cand + l]) { p = p + l + 1; l  = 0; }
		if(s[ (p + l) % n] < s[cand + l]) { cand = max(p, cand + l + 1); p = cand + 1; l = 0; }

	}

	fout << cand << '\n';

	return 0;
}