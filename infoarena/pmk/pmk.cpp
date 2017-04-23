#include <bits/stdc++.h>

using namespace std;

ifstream fin("pmk.in");
ofstream fout("pmk.out");

const int NMAX = 1e4 + 4;

int n, cnt;
int v[NMAX];
int s[NMAX];
int trans[NMAX];
int finish[NMAX];
vector<int> dif[NMAX];
vector<int> aux;

int main() {

	fin >> n ;

	for(int i = 1; i <= n ; ++i)
		fin >> v[i], v[i - 1] = v[i];

	s[1] = cnt;
	trans[0] = 0;
	finish[0] = 1;
	cnt++;

	int p = 0;

	for(int i = 2; i <= n ; ++i) {

		aux.clear();
		
		while(p > 0 && p + 1 != v[i]) { //retin toate diferentele din kmp
			aux.push_back(s[p + 1]);
			p = v[p];
		}

		if(v[i] != 0) {//stiu ca e egal cu cineva
			s[i] = s[v[i]];
		} else {

			aux.push_back(s[1]);//ultima diferenta
			s[i] = cnt++;//nu stiu daca e egal cu cineva
			trans[cnt - 1] = cnt - 1;
		}

		p = v[i];

		for(int x : aux)
			dif[s[i]].push_back(x);
	}

	int must[32];

	for(int i = 2; i < n ; ++i) {

		if(finish[ trans[s[i]] ] == 1) continue;

		memset(must, 0, sizeof(must));

		for(int x : dif[s[i]])
			if(trans[x] < 32)
				must[trans[x]] = 1;

		int choice = 0;
		for( ; choice < 32; ++choice)
			if(must[choice] == 0)
				break;

		trans[s[i]] = choice;
		finish[choice] = 1;
	}

	for(int i = 1; i < n ; ++i)
		fout << (char) ('a' + trans[s[i]]);
	fout << "a\n";

	return 0;
}