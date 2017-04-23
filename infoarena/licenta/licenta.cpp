#include <bits/stdc++.h>
 
using namespace std;
 
 
ifstream fin("licenta.in");
ofstream fout("licenta.out");
 
const int NMAX = 100006;
 
 
int k; int n; int m;
struct interval {
 
    int x; int y;
 
    interval(int x, int y) {
 
        this->x = x;
        this->y = y;
 
    }
 
    interval() {
 
    }
};
 
interval v[NMAX], a[NMAX];
 
 
int st ; int dr;
 
 
bool cmp(interval A, interval B) {
 
    return (A.x < B.x) || (A.x == B.x && A.y < B.y);
}
 
 
int main() {
 
    fin >> k;
    fin >> n ;
     
 
    for(int i = 1 ; i <= n ; ++i) {
 
        fin >> v[i].x >> v[i].y;
 
    }
      
     fin >> m ;
      
     for(int i = 1 ; i <= m ; ++i)
        fin >> a[i].x >> a[i].y ;
 
 
    sort(v  +1, v + n  + 1, cmp);
    sort(a + 1, a + m  + 1, cmp);
 
    int j = 1;
    int last = 1;
 
     
    for(int i = 1; i <= n ; ++i) {
 
        j = last;
        while(v[i].x >= a[j].y)
            j++;
 
        last = j;
         
        while(j <= m && a[j].x < v[i].y) {
 
            if(dr - st < -max(a[j].x, v[i].x) + min(v[i].y, a[j].y)) {
 
                dr = min(v[i].y, a[j].y);
                st =  max(a[j].x, v[i].x);
                 
                if(dr - st >= k ) {
                    fout << st << " " << st + k ;
                    return 0;
                }
            }
 
            j++;
        }
    }
 
 
    return 0;
}   