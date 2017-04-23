#include <bits/stdc++.h>


using namespace std;

ifstream fin("adn.in");
ofstream fout("adn.out");

const int NMAX = 18;
const int LMAX = 3e5 + 5;
const int INF = 0x3f3f3f3f;

int n; int m;

int v[NMAX];

char s[NMAX][LMAX];
int len[NMAX];
int prev1[NMAX][LMAX];
int cost[NMAX][NMAX];
int d[1<<NMAX][NMAX];//d[i][j] = drumul minim cu configuratia i care se termina in j, inclusiv
bool useless[NMAX];
int ant[1<<NMAX][NMAX];
vector<int> ans;

void read() {

	fin >> n;

	for(int i = 0; i < n; ++i)
		fin >> s[i] + 1, len[i] = strlen(s[i] + 1);
}

void solve() {

	for(int i = 0 ; i < n; ++i) {

		int pos = 0;
		prev1[i][1] = 0;

		for(int j = 2; j <= len[i]; ++j) {

			while(pos > 0 && s[i][pos + 1] != s[i][j])
				pos = prev1[i][pos];

			if(s[i][pos + 1] == s[i][j])
				pos++;

			prev1[i][j] = pos;
		}
	}

	for(int i = 0 ; i < n; ++i) {

		if(useless[i] == true) continue;

		for(int j = 0 ; j < n; ++j) {

			if(i == j) continue;
			if(useless[j] == true) continue;

			int pos = 0;
			//i -> j
			for(int k = 2; k <= len[i]; ++k) {
				
				while(pos > 0 && s[j][pos + 1] != s[i][k])
					pos = prev1[j][pos];

				if(s[j][pos + 1] == s[i][k]) pos++;

				if(pos == len[j]) {
					useless[j] = true;
					cost[i][j] = 0;
					break;
				}
			}

			cost[i][j] = len[j] - pos;//cat ma costa sa.l lipesc pe j la i
		}
	}

	for(int i = 0 ; i < n ; ++i)
		if(useless[i] == false)
			v[m++] = i;

}

int main() {

	read(); solve();

	int all = (1 << m) - 1;

	for(int i = 0 ; i <= all ; ++i)
		for(int j = 0 ; j < m; ++j)
			d[i][j] = INF;

	for(int i = 0 ; i < m; ++i)
		d[ 1 << i ][i] = len[ v[i] ] ;//pos sa incep de oriunde

	for(int i = 1 ; i <= all ; ++i) {

		for(int j = 0 ; j < m ; ++j) {
			//j -> k
			if( ! ( (1 << j) & i)) continue;
			for(int k = 0 ; k < m ; ++k) {

				if( (1 << k) & i) continue;

				if(d[i + (1 << k)][k] > d[i][j] + cost[ v[j] ][ v[k] ]) {
					d[i + (1 << k)][k] = d[i][j] + cost[ v[j] ][ v[k] ] ;
					ant[i + (1 << k)][k] = j;
				}
			}
		}
	}

	int last = 0;
	int conf = all;

	for(int i = 0 ; i < m ; ++i) 
		if(d[all][last] > d[all][i])
			last = i;

	for(int i = 0 ; i < m ; ++i) {

		ans.push_back(v[last]);
		int aux = last;
		last = ant[conf][last];
		conf = conf - (1 << aux);
	}

	reverse(ans.begin(), ans.end());

	for(int i = 0 ; i < ans.size(); ++i)
		if(i == 0)
			fout << s[ ans[i] ] + 1;
		else 
			fout << s[ ans[i] ] + 1 + (len[ans[i]] - cost[ ans[i - 1] ][ ans[i] ]);

	return 0;
}