#include <cstdio>
#include <vector>
#include <queue>
#define nmax 500010
#define inf 1<<30
 
using namespace std;
 
struct vecini
{
    int vec,c; int ind;
};
 
vector<vecini> v[nmax];
int n,m,cost[nmax],prez[nmax];
int  T[nmax]; int M[nmax];
int T1;
int viz[nmax];

 
void citire()
{
    int i,x;
    vecini vc;
	
		
	scanf("%d%d",&n,&m);
	printf("%d %d ", n, m);
		
	for(i=1;i<=m;i++)		    {
		      scanf("%d%d%d",&x,&vc.vec,&vc.c);
			vc.ind = i;
		    v[x].push_back(vc);
		    }
	for(i=2;i<=n;i++)
	    cost[i]=inf;

}
 
struct cmp
{
    bool operator()(const int& a, const int& b)
    {
        return cost[a]>cost[b];
    }
};
 
void dijkstra()
{
    priority_queue<int, vector<int>, cmp> q;
    q.push(1);
	for(int i = 0 ; i <= n; ++i)
		prez[i] = T[i] = M[i] =  viz[i] = 0;
    prez[1]=1;
	T[1] = 1;
	M[1] = 0;
	cost[1] = 0;
    vecini vc;
    int p,i,c;
    while(!q.empty())
          {
              p=q.top();
              q.pop();
              for(i=0;i<v[p].size();i++)
                  {
                      vc=v[p][i];
                      c=cost[p]+vc.c;
                      if(c<cost[vc.vec])
                         {
                             cost[vc.vec]=c;
							 T[vc.vec] = p;
							 M[vc.vec] = v[p][i].ind;
							
                             if(!prez[vc.vec])
                                {
                                    prez[vc.vec]=1;
                                    q.push(vc.vec);
                                }
                         }
                  }
              prez[p]=0;
          }
}
int check[2 * nmax];

void dute(int x) {
	
	int g[nmax];
	//printf("%d", x);
	
	for(g[0] = 0 ; viz[x] == 0;  ) {
			g[++g[0]] = M[x];	
			viz[x] = 1;
			x = T[x];
			
	}
	//printf("%d", g[0]);
	for(int i = g[0];  i > 0; --i)	
		if(g[i])	{	
			printf("%d ", g[i]);
			check[g[i]] = 1;
		}
	
}
 
void afisare()
{

	
   for(int i=1;i<=m;i++)
  		check[i] = 0;

	//for(int i = 1; i <= n; ++i)
			printf("%d ", viz[i]);		
		if(!viz[i])
			dute(i);
	for(int i = 1; i <= m; ++i)
		if(check[i] == 0)
			printf("%d ", i);
	printf("\n");*/
}
 
int main() {
    
	freopen("algoritm.in","r",stdin);
    freopen("algoritm.out","w",stdout);
    citire();
    scanf("%d", &T1);
	printf("%d\n", T1);
	for(int k = 1; k <= T1; ++k) {
		
		citire();
 		dijkstra();
    	afisare();
		for(int i = 0; i <= n; ++i)
			v[i].clear();
	}
    return 0;
}
