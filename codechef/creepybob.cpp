#include <algorithm>
#include <vector>
#include <cstdlib>
#include <cstdio>

using namespace std;


int t;
int n;

const int NMAX = 500005;

int a[NMAX];

vector<int> g[NMAX];

bool mark[NMAX];

int he[NMAX];

int lant[NMAX];

vector<int> sol;

int calch(int x) {

	int max_h = 0 ;

	for(unsigned i = 0 ; i < g[x].size(); ++i) {

		int k = calch(g[x][i]);

		if(mark[g[x][i]] == 0)
			max_h = max(max_h, k);

	}

	he[x] = max_h + 1;

	return max_h + 1;
}

void reset() {

	for(int i = 0 ; i <= n; ++i) {
		g[i].clear();
		mark[i] = 0;
		he[i] = 0;
		lant[i] = 0;
	}
}

int main() {

	scanf("%d", &t);

	while(t--) {

		scanf("%d", &n);
		
		for(int i = 0 ; i < n ; ++i) {

			int x;
			scanf("%d", &x);

			if(x == -1)
				x = n ;
			a[i] = x;

			g[x].push_back(i);

		}

		int nod = 0;

		mark[0] = 1;
		
		while(nod != n) {
			
			lant[a[nod]] = lant[nod] + 1;
			nod = a[nod];
			mark[nod] = 1;

		}

		

		nod = 0;
		
		int ans = lant[n];

		int s = calch(n);

		while(nod != n) {

			nod = a[nod];

			ans = max(ans, he[nod] + lant[n] - 1);

		}


		sol.push_back(ans);

	}
	
	for(int i = 0 ; i < sol.size(); ++i)
		printf("%d\n", sol[i]); 

	

	return 0;
}