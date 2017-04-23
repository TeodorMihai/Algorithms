#include <bits/stdc++.h>
 
using namespace std;
 
#define pp pair<int, int>
#define x first
#define y second
 
const int NMAX = 1004;
const int DIMBUF = 5e6 + NMAX;
 
int n; int m; int p;
 
int a[NMAX][NMAX];
 
deque<int> qmin[NMAX];
deque<int> qmax[NMAX];
 
int ans = 0x3f3f3f3f;
int cnt = 0;

char buff[DIMBUF]; int pos; int len;
   
int get(int& x) {
   
    while(pos < len && !('0' <= buff[pos] && buff[pos] <= '9' ) ) {
        ++pos;
    }
   
    x = 0;
    while(pos < len && '0' <= buff[pos] && buff[pos] <= '9')  {
        x = x * 10 + buff[pos] - '0';
        ++pos;
    }
}
 
void find(int dx, int dy) {//dx * dy
 
    for(int i = 1; i <= max(n, m); ++i) {
        qmax[i].clear(); qmin[i].clear();
    }
    deque<pp> qlow;
    deque<pp> qhigh;
 
    for(int j = 1 ; j <= m; ++j) {
 
        for(int i = 1; i <= n; ++i) {
 
            //actulizez cozile pe orizonatala
            while(qmin[i].empty() == false && a[i][qmin[i].back()] >= a[i][j])
                qmin[i].pop_back();
 
            qmin[i].push_back(j);
 
            if(qmin[i].empty() == false && j - qmin[i].front() + 1 > dy)
                qmin[i].pop_front();
 
 
            while(qmax[i].empty() == false && a[i][qmax[i].back()] <= a[i][j])
                qmax[i].pop_back();
 
            qmax[i].push_back(j);
 
            if(qmax[i].empty() == false && j - qmax[i].front() + 1 > dy)
                qmax[i].pop_front();
        }
 
        qlow.clear();
        qhigh.clear();
 
        for(int i = 1; i <= n; ++i) {
 
            while(qlow.empty() == false && qlow.back().x >= a[i][qmin[i].front()])
                qlow.pop_back();
 
            qlow.push_back({a[i][qmin[i].front()] , i});
 
            if(qlow.empty() == false && i - qlow.front().y + 1 > dx)
                qlow.pop_front();
 
 
            while(qhigh.empty() == false && qhigh.back().x <= a[i][qmax[i].front()])
                qhigh.pop_back();
 
            qhigh.push_back({a[i][qmax[i].front()] , i});
 
            if(qhigh.empty() == false && i - qhigh.front().y + 1 > dx)
                qhigh.pop_front();
 
            if(j >= dy && i >= dx) {
 
                if(qhigh.front().x - qlow.front().x == ans) 
                    cnt++;
 
                if(qhigh.front().x - qlow.front().x < ans) {
                    ans = qhigh.front().x - qlow.front().x;
                    cnt = 1;
                }
 
            }
 
        }
    }
}
 
int main() {

	freopen("struti.in", "r", stdin);
    freopen("struti.out", "w", stdout);
    fread(buff, 1, DIMBUF, stdin);
    len = strlen(buff);
    get(n); get(m); get(p);
 
    for(int i = 1; i <= n; ++i) 
        for(int j = 1; j <= m ; ++j)
            get(a[i][j]);
 
    while(p--) {
 
        int dx , dy;
 		get(dx); get(dy);
		ans = 0x3f3f3f3f;
        cnt = 0;
        find(dx, dy);
        if(dx != dy)
            find(dy, dx);
 
        printf("%d %d\n", ans, cnt);
    }
 
 
    return 0;
}