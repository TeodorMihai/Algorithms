#include <bits/stdc++.h>

using namespace std;

ifstream fin("radio2.in");
ofstream fout("radio2.out");

const int NMAX = 1e6 + 5;
const int MMAX = 500;
const int MOD = 666013;
const int KMAX = 50;
const int LMAX = 2505;
const int ALPHA = 29;
int n; int m; int l; int k; int dim;

char s[NMAX]; char q[LMAX];

vector<int> hash1[MOD];
int put[LMAX];
int getn[255];
set<int> tried;


void ins(int key, int val) {

	hash1[key].push_back(val);
}

int match(int ind, int h) {

	for(int i : hash1[h]) {

		int cnt = 0;
		int difHash = 0;
		
		if(tried.find(i - ind + 1) != tried.end()) continue;

		if(strncmp(q + ind, s + i, dim) != 0) continue;
		
		tried.insert(i - ind + 1);

		for(int j = 1; j <= l ; ++j) 
			if(q[j] != s[i - ind + j]) {
				cnt++;
				if(cnt > k) break;
			}
		

		if(cnt <= k)
			return 1;
	}

	return 0;
}



int main() {

	std::ios_base::sync_with_stdio(false);

	fin >> n >> m >> l >> k;

	for(char i = 'a'; i <= 'z' ; ++i)
		getn[i] = i - 'a' + 1;

	fin >> (s + 1);
	if(k != 0)
		dim = (l - k) / (k + 1) + 1;
	else 
		dim = l;

	put[0] = 1;
	put[1] = ALPHA;
	for(int i = 1; i < dim; ++i)
		put[i] = (put[i - 1] * ALPHA) % MOD;

	int h = 0;

	for(int i = 1 ; i <= dim ; ++i) 
		h = (h * ALPHA + getn[s[i]]) % MOD;
	ins(h, 1);

	for(int i = dim + 1; i <= n; ++i) {

		h = (h - getn[s[i - dim]] * put[dim - 1]) % MOD;
		if(h < 0)
			h += MOD;
		h = (h * ALPHA + getn[s[i]]) % MOD;
		ins(h, i - dim + 1);
	}

	for(int j = 1; j <= m ; ++j) {

		fin >> (q + 1);
		tried.clear();

		h = 0;

		for(int i = 1 ; i <= dim ; ++i) 
			h = (h * ALPHA + getn[q[i]]) % MOD;

		if(match(1, h) == 1) {
			fout << 1 << '\n';
			continue;
		}

		int ok = 0;

		for(int i = dim + 1; i <= l; ++i) {

			h = (h - getn[q[i - dim]] * put[dim - 1]) % MOD;
			if(h < 0)
				h += MOD;
			h = (h * ALPHA + getn[q[i]]) % MOD;

			if(match(i - dim + 1, h)) {
				fout << 1 << '\n';
				ok = 1;
				break;
			}
		}

		if(ok == 0)
			fout << 0 << '\n';
	}



	return 0;
}