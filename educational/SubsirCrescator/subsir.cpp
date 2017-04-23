#include <bits/stdc++.h>

using namespace std;

ifstream fin("scmax.in");
ofstream fout("scmax.out");

const int NMAX = 100001;

int n;

int best[NMAX];
int ai[NMAX * 4];
int v[NMAX];
int s[NMAX];

// best[i] = lungimea celui mai lung subsir crescator care il include pe v[i]

//Idea: Vrem  la pasul j best[i] , cu  i = 1..j si a[i] > a[j]. Folosim un aib, sortam inainte elementele ca sa avem un interval
//clar in care cautam, daca un element nu a fost analizat inca o sa aiba best[x] = 0 deci nu o sa intre in niciun fel in solutie

//s - indicii lui v sortati dupa valorile in v, s[1] = indicele celui mai mci element in v
//ai - arborele, 

void update(int vertex, int left , int right, const int& pos,const int& value) {
 
	if(left == right) {

		ai[vertex] = value;
		return; 
	}
	
	int middle = (left + right) / 2;

	if(pos <= middle) update(vertex * 2, left, middle , pos, value);
	else update(vertex * 2 + 1, middle + 1, right, pos, value);

	ai[vertex] = ai[vertex * 2];

	if(best[s[ai[vertex * 2 + 1]]] > best[s[ai[vertex]]])
		ai[vertex] = ai[vertex * 2 + 1];
}


int find(int x) {

	int pos; int byte = 1;

	for( ; byte <= n ; byte <<= 1);

	for(pos = 0 ; byte; byte >>= 1)
		if(pos + byte <= n && v[s[pos + byte]] < x )
			pos += byte;
	return pos;
}

int query(int vertex, int left, int right,const int& last) {

	if(right <= last) 
		return ai[vertex];

	int middle = (left + right) / 2;
	int maxim = 0;

	if(left <= middle)
		maxim = max(best[ s[ maxim] ], best[ s[ ai[query(vertex * 2, left , middle, last)] ] ] );

	if(middle + 1  <= last)
		maxim = max(best[ s[ maxim] ], best[ s[ ai [ query(vertex * 2 + 1, middle + 1, right, last) ] ] ]) ;
	return maxim;
}

bool comp(int x, int y) {
;
	return v[x] < v[y];
}

int main() {

	fin >> n;

	for(int i = 1 ; i <= n ; ++i) {

		fin >> v[i];
		s[i] = i;
	}

	sort(s + 1, s + 1 + n, comp);

	best[1] = 1;
	update(1, 1, n, 1, 1);

	for(int i = 1 ; i <= n ; ++i)
		fout << v[s[i]] << " ";

	for(int i = 2; i <= n; ++i) {

		int index = find(v[i]);
		int in = query(1, 1, N, index);//indicele din s care are best[s[i]] = max
		update(1, 1, N, in);

	}

	return 0;
}