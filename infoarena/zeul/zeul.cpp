#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("zeul.in");
ofstream fout("zeul.out");
 
 
const int NMAX = 100002;
 
int n, m;
 
 
int in[NMAX], out[NMAX]; int dif[NMAX];
 
queue<int> q1;
queue<int> q2;
 
vector< pair<int, int> > v;
 
int main() {
 
    fin >> n >> m;
    for(int i = 0 ; i < m; ++i) {
 
        int x, y;
        fin >> x >>y;
        in[y]++;
        out[x]++;
    }
 
    for(int i = 1; i <= n; ++i) {
 
        dif[i] = in[i] - out[i];
        if(dif[i] < 0)
            q1.push(i);
        if(dif[i] > 0)
            q2.push(i);
    }
 
    while(!q1.empty() ) {
 
        int x = q1.front();
         
        int y = q2.front();
 
        while(dif[x] != 0 && dif[y] != 0)  {
 
            v.push_back(make_pair(y, x));
            dif[x]++;
            dif[y]--;
        }
 
        if(dif[x] == 0)
            q1.pop();
         
        if(dif[y] == 0)
            q2.pop();
 
 
 
    }
 
    fout << v.size() << '\n';
    for(int i = 0 ; i < v.size(); ++i)
        fout << v[i].first << " " << v[i].second << '\n';
 
    return 0;
}