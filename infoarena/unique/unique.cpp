#include <bits/stdc++.h>

using namespace std;

ifstream fin("unique.in");
ofstream fout("unique.out");

#define pp pair<int, int>

const int NMAX = 1e5 + 5;

int n;

int v[NMAX];
int s[NMAX];
int pre[NMAX];
int nex[NMAX];
int lst[NMAX];
int aib[NMAX];

vector<pp> queries[NMAX];

char buffer[NMAX * 10 * 6]; int ind; int m;

int getNext() {

	int nr = 0;

	while(ind < m && (buffer[ind] == ' ' || buffer[ind] == '\n')) ind++;

	while(ind < m && '0' <= buffer[ind]  && buffer[ind] <= '9') 
		nr = nr * 10 + buffer[ind] - '0', ind++;

	return nr;
}

//pentru fiecare element retin cel mai apropiat element ai mare strict decat el
//din dreapta si din stanga,0 sau n + 1 daca nu exista
void findNeighbours() {

	s[0] = 0;

	for(int i = 1; i <= n ; ++i) {
		while(s[0] > 0 && v[s[s[0]]] <= v[i])
			s[0]--;
		pre[i] = s[s[0]];
		s[++s[0]] = i;
	}

	s[0] = 0;

	for(int i = n ; i > 0 ; --i) {
		while(s[0] > 0 && v[s[s[0]]] <= v[i])
			--s[0];
		if(s[0] == 0)
			nex[i] = n + 1;
		else 
			nex[i] = s[s[0]];

		s[++s[0]] = i;
	}
}

void ins(int pos, int value) {

	for( ; pos <= n ; pos += pos & -pos)
		aib[pos] += value;
}

int query(int pos) {

	int sum = 0;

	for( ; pos > 0 ; pos -= pos & -pos)
		sum += aib[pos];

	return sum;
}

int main() {

	fin.get(buffer, NMAX * 10 * 6, '\0');
	m = strlen(buffer);
	int t; 

	t = getNext();

	while(t--) {

		n = getNext();

		for(int i = 1; i <= n ; ++i) 
			v[i] = getNext(), queries[i].clear(), aib[i] = 0, lst[i] = 0;

		findNeighbours();

		//facem queriuri sa aflam cate elemente distince sunt in intervalul pre[i] - 1, nex[i] + 1
		for(int i = 1; i <= n ; ++i)
			queries[nex[i] - 1].push_back({pre[i] + 1, i});

		int maxi = -1;
		int all = 0;

		for(int i = 1; i <= n ; ++i) {
			
			ins(i, 1); all++;

			if(lst[v[i]] != 0)
				ins(lst[v[i]], -1), all--;

			lst[v[i]] = i;

			for(unsigned j = 0 ; j < queries[i].size() ; ++j) {

				pp p = queries[i][j];
				if(i - p.first + 1 < maxi) continue;
				if(j != 0 && p.first == queries[i][j - 1].first) continue; 

				int sol =  all - query(p.first - 1);

				if(sol >= v[p.second] && maxi < i - p.first + 1)
					maxi = i - p.first + 1;
			}
		}

		fout << maxi << '\n';
	}

	return 0;
}