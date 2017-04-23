#include <bits/stdc++.h>

using namespace std;

ifstream fin("invsort.in");
ofstream fout("invsort.out");

const int NMAX = 32009;
const int MAXVAL = 32000;

int n; int v[NMAX];int b[NMAX]; int cnt[NMAX];

vector< pair<int, int> > sol;

void rev(int st, int middle, int dr) {

	int left = middle;
	bool ok1 = false; bool ok2 = false;

	while(left >= st && b[left] == 1)
		left--, ok1 = true;
	left++;

	int right = middle + 1;

	while(right <= dr && b[right] == 0)
		right++, ok2 = true;

	right--;

	if(ok1 && ok2) {
		sol.push_back({left, right});
		while(left < right)
			swap(v[left], v[right]), swap(b[left], b[right]), ++left, --right;
	}

}


void invsort(int st, int dr) {

	if(st >= dr) return;

	int mid = (st + dr) / 2;

	invsort(st, mid);
	invsort(mid + 1, dr);

	rev(st, mid, dr);
}

void quicksort(int st, int dr) {

	if(dr <= st)
		return ;

	int mid = (st + dr) / 2;

	for(int i = st; i <= dr; ++i)
		b[i] = (v[i] >= mid);

	invsort(st, dr);
	
	quicksort(st, mid);
	quicksort(mid + 1, dr);
}

int main() {

	srand(time(NULL));
	
	fin >> n ;

	for(int i = 1; i <= n ; ++i)
		fin >> v[i], cnt[v[i]]++;

	for(int i = 0; i < MAXVAL; ++i)
		cnt[i] += cnt[i - 1];

	//cnt[x] = cate sunt mai mici sau egale cu x
	for(int i = 1; i <= n; ++i)
		v[i] = cnt[v[i]]--, v[i]--;
	
	quicksort(1, n);

	//for(int i = 1; i <= n; ++i)
	//	cout << v[i] << '\n';

	for(auto p : sol)
		fout << p.first << ' ' << p.second << '\n';

	return 0;
}