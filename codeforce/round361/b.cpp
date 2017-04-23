#include <bits/stdc++.h>
 
 
using namespace std;
 
#define pair pair<int, int>
 
const int NMAX = 200008;
const int INF = 0x3f3f3f3f;
 
int n; int m;
 
vector< vector< pair > > g(NMAX + 1, vector< pair >(0) );
 
vector<int> dist(NMAX + 1, INF);
 
void read() {
 
    cin >> n ;
 
    for(int i = 1; i <= n ;++i) {
         
        int x; int y; int cost;
        cost = 1;
        x = i;
        cin >> y ;
        g[x].push_back({y, cost});
    }

    for(int i = 1; i < n; ++i) {
    	g[i].push_back({i + 1, 1});
    	g[i + 1].push_back({i, 1});

    }
}
 
void dijkstra(int source, int dest, vector< vector< pair> >& g) {
 
    priority_queue<pair, vector<pair>, greater<pair> > pq;
 
    dist[source] = 0;
    pq.push({0, source});
 
    while(pq.empty() == false) {
 
        int node = pq.top().second;
        int dst = pq.top().first;   
         
        pq.pop();
 
        if(dist[node] < dst) continue;
 
        for(pair x : g[node]) {
 
            if(dist[node] + x.second < dist[x.first]) {
 
                dist[x.first] = dist[node] + x.second;
                pq.push({dist[x.first], x.first});
            }
        }
    }
}

int modulo(int x) {
	return x < 0 ? -x : x;
}
 
int main() {
 
    read();
 
    dijkstra(1, n, g);
  
    for(int i = 1; i <= n ; ++i)
         cout << dist[i] << ' ';
     cout << '\n'; 
 
    return 0;
}