#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>

#define MAX 100003
const long long INFINITE = (1<<50);
using namespace std;
 
ifstream fin("tempest.in");
ofstream fout("tempest.out");
 
vector < pair <long long,long long> > la[MAX];
 
long long d[MAX],n,m,tata[MAX]; long long S; long long D; long long drum[MAX]; long long K; long long T;
 
class cmp
{
public:
    bool operator()(pair<long long, long long> a, pair<long long, long long> b)
    {
        return a.second>b.second;
    }
};
 

 

 vector<long long> rez;
void dijkstra(long long nod)
{
    long long u,v,w;
    priority_queue<pair<long long, long long>,vector<pair<long long, long long> >,cmp> pq;
    for(long long i=1;i<=n;i++) d[i]=INFINITE, tata[i] = 0;
    tata[nod]=d[nod]=0;
    pq.push(make_pair(nod, 0));
 
    while(!pq.empty())
    {
        u=pq.top().first;
        pq.pop();
        for(unsigned i=0;i<la[u].size();i++)
        {
            v=la[u][i].first;
            w=la[u][i].second;
            if(d[v]>d[u]+w)
            {
                d[v]=d[u]+w;
                tata[v]=u;
                pq.push(make_pair(v, d[v]));
            }
        }
 
    }
 
}
 
void afis()
{
    for(long long i=2;i<=n;i++)
        if(d[i]==INFINITE)
            fout<<0<<' ';
        else
            fout<<d[i]<<' ';
}

struct muchie{

    long long x; long long y; long long cost;
};

muchie M[3 * MAX];
 
long long cost_total[MAX];

int main()
{
    fin >> T;
    while(T --) {
        fin >> n >> m >> S >> D;

        for(long long i=1; i<=m ;i++) {

            long long u,v,w;
            fin>>u>>v>>w;
            la[u].push_back(make_pair(v, w));
            la[v].push_back(make_pair(u, w));
            M[i].x = u;
            M[i].y = v;
            M[i].cost = w;
        }
          fin >> K;
        long long x; 
        cost_total[0] = 0;
        for(long long i = 1; i <= K; ++i)  {
            
            fin >> drum[i];
            cost_total[i] = cost_total[i - 1] +  M[drum[i]].cost;
        }

        dijkstra(D);
      
        for(long long i = 1; i <= n; ++i) {
            //fout << d[i] <<" ";
            if(cost_total[K] >= d[i])
                rez.push_back(i);

        }

        sort(rez.begin(), rez.end());
        
        fout << rez.size() << '\n';
        for(unsigned i = 0 ;i < rez.size(); ++i)
            fout << rez[i] << " ";
        
        fout << '\n';
        
        rez.clear();
        for(long long i = 1; i <= n; ++i)
                la[i].clear();

    }


    return 0;
}