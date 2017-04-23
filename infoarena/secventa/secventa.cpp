#include <bits/stdc++.h>

using namespace std;

#define pp pair<int, int>
#define x first
#define y second

const int DIMBUF = 1e6;

int n; int k; int b = -0x3f3f3f3f;
int a;
int st, dr;
deque<pp> q;

char buff[DIMBUF]; int p; int len;
  
int get(int& x) {
  	
  	int sgn = 1;

    while(p < len && !('0' <= buff[p] && buff[p] <= '9' ) ) {

    	if(buff[p] == '-')
    		sgn = -1;
        ++p;
        if(p == DIMBUF)
            fread(buff, 1, DIMBUF, stdin), p = 0, len = strlen(buff);
    }
  
    x = 0;
    while(p < len && '0' <= buff[p] && buff[p] <= '9')  {
        x = x * 10 + buff[p] - '0';
        ++p;
        if(p == DIMBUF)
            fread(buff, 1, DIMBUF, stdin), p = 0 , len = strlen(buff);
  
    }

    x *= sgn;
}


int main() {

	freopen("secventa.in", "r", stdin);
    freopen("secventa.out", "w", stdout);
    fread(buff, 1, DIMBUF, stdin);
    len = strlen(buff);
    get(n); get(k);
 
	//j1 < j2 , a[j1] > a[j2], j1 poate fi eliminat

	for(int i = 1; i <= k - 1; ++i) {

		get(a);
		while(q.empty() == false && q.back().first >= a)
			q.pop_back();

		q.push_back({a, i});
	}

	for(int i = k; i <= n ; ++i) {

		get(a);

		while(q.empty() == false && q.back().first >= a)
			q.pop_back();

		q.push_back({a, i});

		if(q.empty() == false && i - q.front().second + 1 > k) 
			q.pop_front();

		if(q.front().first > b) {
			b = q.front().first;
			st = i - k + 1;
			dr = i;
		}
	}

	printf("%d %d %d\n", st, dr, b);

	return 0;
}
