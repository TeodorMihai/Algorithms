#include <bits/stdc++.h>


using namespace std;

#define pp pair<int, int>

std::ifstream fin ("dijkstra.in");
std::ofstream fout("dijkstra.out");

const int NMAX = 50001;
const int MMAX = 250000;
const int INF = (1<<30);

int N; int M; int dist[NMAX];

std::vector< std::pair<int, int> > G[NMAX];

int in[NMAX]; int viz[NMAX];
int hasC = false;


void read() {

	fin >> N >> M;

	int x; int y; int cost; 

	for(int i = 0 ;i < M; ++i) {

		fin >> x >> y >> cost;

		G[x].push_back(std::make_pair(y, cost));
		in[y]++;

	}
}



bool hasCycle(int x) {

	viz[x] = 1;//gri

	for(pp node : G[x])
		if(viz[node.first] == 1)
			hasC = true;
		else if(viz[node.first] == 0) //alb
			hasCycle(node.first);

	viz[x] = 2;//negru
}


int* Dijkstra(int start) {

	int *dist = new int[NMAX];

	for(int i = 1 ; i <= N; ++i)
		dist[i] = INF;
	
	dist[start] = 0;
	queue<int> q;

	for(int i = 1; i <= N; ++i)
		if(in[i] == 0)
			q.push(i);

	while(q.empty() == false) {

		int nod = q.front();
		q.pop();

		for(pp x : G[nod]) {

			if(dist[x.first] > dist[nod] + x.second)
				dist[x.first] = dist[nod] + x.second;

			in[x.first]--;

			if(in[x.first] == 0)
				q.push(x.first);
		}
	}
	return dist;
}

int main() {

	read();


	for(int i = 1; i <= N; ++i)
		if(viz[i] == 0)
			hasCycle(i);

	if(hasC == true) 
		fout << "graf ciclic\n"; 
	 else {
		int *dist = Dijkstra(1);

		for(int i = 2 ; i <= N; ++i )
			if(dist[i] == INF)
				fout << 0 << " ";
			else fout << dist[i] << " ";

	}

	return 0;
}

