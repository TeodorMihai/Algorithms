#include <bits/stdc++.h>
#include <stdio.h>
 
using namespace std;
 
ifstream fin("dijkstra.in");
ofstream fout("dijkstra.out");
 
template<class Type = int>
class Less {
 
public:
    bool operator() (const Type& a, const Type& b) {
        return a < b;
    }
};
 
template<class Type = int>
class Greater {
 
public:
    bool operator() (const Type& a, const Type& b) {
        return  b < a;
    }
};
 
template<class Type = int, class Container = vector<Type> , class Comp = Greater<> >
class Heap {
 
private:
    Container heap;
    Comp comp;
 
    inline int father(int node) {
        return (node - 1) / 2;
    }
 
    inline int leftSon(int node) {
        return node * 2 + 1;
    }
 
    inline int rightSon(int node) {
        return node * 2 + 2;
    }
 
    void up(int current) {
 
        if(current == 0) return ;
 
        if(comp(heap[father(current)], heap[current]) == true) {
            swap(heap[father(current)], heap[current]);
            up(father(current));
        }
    }
 
    void down(int current) {
 
        int substitute = current;
         
        if(leftSon(current) < heap.size() && comp(heap[substitute], heap[leftSon(current)]) == true)
            substitute = leftSon(current);
 
        if(rightSon(current) < heap.size() && comp(heap[substitute], heap[rightSon(current)]) == true)
            substitute = rightSon(current);
 
        if(current != substitute) {
            swap(heap[substitute], heap[current]);
            down(substitute);
        }
    }
 
public:
    Heap() { }
     
     
    bool empty() const {
        return heap.empty();
    }
 
    int size() const {
        return heap.size();
    }
 
    const Type& top() const {
        return heap.front();
    }
 
    void push(const Type& val) {
 
        heap.push_back(val);
        up(heap.size() - 1);
    }
 
    void pop() {
 
        swap(heap.front(), heap[heap.size() - 1]);
        heap.pop_back();
        down(0);
    }
  
};
 
template<class Type = int>
class Edge {
 
private:
    int node;
    Type cost;
 
public:
    Edge() { }
    Edge(int node, Type cost) {
        this->node = node;
        this->cost = cost;
    }

    friend bool operator< (const Edge&  a, const Edge& b) {
        return a.cost < b.cost;
    }
  
    inline int getNode() const { return node; }
    inline Type getCost() const { return cost; }
 
};

 
template<class Type = int , class Edge = Edge<int> >
class WeightedGraph {
 
private:
     
    const int nVertices;
    vector< vector< Edge > > graph;
 
public:
    const Type INF = numeric_limits<Type>::max();
 
    WeightedGraph() {}
    WeightedGraph(int nVertices) : nVertices(nVertices) {
        graph.resize(nVertices + 1, vector<Edge>());
    }
 
    void addEdge(int x, int y, Type c) {
        graph[x].push_back(Edge(y, c));
    }
 
    const vector<Type> getDistances(int source) const {
 
        Heap<Edge , vector<Edge> , Greater<Edge> > heap;
        vector<Type> distances(nVertices + 1, INF);
        vector<bool> visited(nVertices + 1, false);
 
        heap.push(Edge(source, 0));
        distances[source] = 0;
 
        for( ; heap.empty() == false; ) {
            int node = heap.top().getNode();
            heap.pop();
 
            if(visited[node] == true) continue;
            visited[node] = true;
 
            for(Edge e : graph[node])
                if(visited[e.getNode()] == false && distances[node] + e.getCost() < distances[e.getNode()]) {
 
                    distances[e.getNode()] = distances[node] + e.getCost();
                    heap.push(Edge(e.getNode(), distances[e.getNode()]));
                }
        }
 
        return distances;
    }
};
 
int main() {
 
    int n , m;
    fin >> n >> m;
 
    WeightedGraph<int, Edge<int> > wg(n);
    while(m--) {
 
        int x, y, c; fin >> x >> y >> c;
        wg.addEdge(x, y, c);
    }
 
    vector<int> dist = wg.getDistances(1);
 
    for(int i = 2; i <= n; ++i)
        if(dist[i] == wg.INF)
            fout << 0 << ' ';
        else
            fout << dist[i] << ' ';
    return 0;
}