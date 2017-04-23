#include <bits/stdc++.h>

using namespace std;


const int NMAX = 500009;

int n, c;
int st = 0, dr = c - 1;

vector<int> a[NMAX];
vector<int> v;

int interval[NMAX * 2];
int sum[NMAX * 2];

struct Cmp {

	int col;
	bool operator()(int x, int y) {
		return a[x][col] < a[y][col];
	}
} cmp;


void notinter(int x, int y) {
	interval[x]++;
	interval[y + 1]--;
}

void cut(int x, int y, int i, int j) {

	if(x == y) return ;
	if(x < y) {
		if(i < j) 
			notinter(c - y + 1, c - x);
		else if(j < i) {
			notinter(0, c - y);
			notinter(c - x + 1, c);
		}
	} else cut(y, x, j, i);
}

void go(vector<int>& v, int col) {

	cmp.col = col;
	sort(v.begin(), v.end(), cmp);

	vector<int> newv;

	for(int i = 0 ; i < v.size(); ++i) {

		if(i == 0) {
			if(a[v[i]].size() > col + 1)
				newv.push_back(v[i]);
			continue;
		}

		int n1 = a[v[i - 1]][col];
		int n2 = a[v[i]][col];

		cut(n1, n2, v[i - 1], v[i]);

		if(a[v[i]].size() > col + 1) {
			if(n1 == n2)
				newv.push_back(v[i]);
			else {
				go(newv, col + 1);
				newv.clear();
				newv.push_back(v[i]);
			}
		}
		
	}
}


int main() {

	cin >> n >> c;

	for(int i = 1; i <= n ; ++i) {
		int l; cin >> l;
		for(int j = 1; j <= l ; ++j) {

			int x; cin >> x;
			a[i].push_back(x);
		}
	}

	for(int i = 1; i <= n ; ++i) 
		v.push_back(i);

	go(v, 0);

	int ans = -1;
	for(int i = 0 ; i <= c; ++i)
		sum[i] = sum[i - 1] + interval[i];

	for(int i = 0 ; i <= c; ++i)
		if(sum[i] == 0)
			ans = 0;

	cout << ans << '\n';
	
	return 0;
}