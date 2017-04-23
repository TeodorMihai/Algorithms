#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("unlock.in");
ofstream fout("unlock.out");
 
const int NMAX = 255;
 
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
 
int n; int m ; int k;
 
vector<int> g[NMAX * NMAX];
vector<int> color[NMAX * NMAX];
//color[i] toate componente care au culoarea i
 
int a[NMAX][NMAX];
int seen[NMAX][NMAX];
int inter[NMAX][NMAX]; //inter[i][j] = numarul corespunzator nodului [i][j]
int cnt;
int mul[NMAX * NMAX];
int r[NMAX* NMAX];
 
bitset<NMAX * NMAX> isGol;
 
 
void neighbours(int x, int y) {
 
    for(int p = 0 ; p < 4; ++p) {
 
        int newX = x + dx[p];
        int newY = y + dy[p];
 
        if(newX == 0 || newY == 0 || newY == m + 1 || newX == n + 1) continue;
        //daca nu fac parte din aceeasi componenta duc muchie,
        // se poate duce o muchie de mai multe ori
        if(inter[x][y] != inter[newX][newY]) {
            g[inter[x][y]].push_back(inter[newX][newY]);
            g[inter[newX][newY]].push_back(inter[x][y]);
        }
    }
}
 
 
void constructInter(int x, int y, int nr, int coresp) {
 
    seen[x][y] = true;
    inter[x][y] = coresp;

    if(a[x][y] == 0)
        isGol[coresp] = 1;
 
    for(int k = 0 ; k < 4; ++k) {
 
        int newX = x + dx[k];
        int newY = y + dy[k];
 
        if(newX == 0 || newY == 0 || newY == m + 1 || newX == n + 1) continue;
 
        if(seen[newX][newY] == false && a[newX][newY] == nr) 
            constructInter(newX, newY, nr, coresp);
    }
}

 
void reset() {
 
    for(int i = 1; i <= n ; ++i)
        for(int j = 1; j <= m ; ++j) 
            seen[i][j] = 0; 
 
    isGol.reset();

    for(int i = 1; i <= cnt; ++i)
        g[i].clear();

    for(int i = 0; i <= k ; ++i)
        color[i].clear();

    cnt = 0;
}

void read() {

     fin >> n >> m >> k;
 
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m ; ++j)
            fin >> a[i][j];
}

void printGraph() {

    for(int i = 1; i <= cnt; ++i) {
        
        cout << i << "   ";

        for(int x : g[i])
            cout << x << ' ' ;
        
        if(isGol[i])
            cout << "gol" << '\n';
        else cout << '\n';  
    }

    cout << "Componente:\n";

    for(unsigned i = 0 ; i <= k; ++i) {

        cout << "culoarea: " << i << "    ";
        
        for(int x : color[i])
            cout << x << ' ';

        cout << '\n'; 
    }
}

int find(int x) {

    if(mul[x] == x) return x;//e radacina
    
    return (mul[x] = find(mul[x]));
}

void unite(int x, int y) {

    if(r[x] > r[y]) 
        mul[y] = x; 
    
    else {
        r[x] = max(r[x] + 1, r[y]);
        mul[x] = y;
    }
}

void solve() {

    //asociem fiecarei casute un nod, cnt cate noduri am 1, cnt

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m ; ++j)
            if(seen[i][j] == false) {
                cnt++;      
                constructInter(i, j, a[i][j], cnt);

                color[a[i][j]].push_back(cnt);
            }

    //construire graf
     
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m ; ++j)
             neighbours(i, j);

    //scoatem muhciile duplicate

    for(int i = 1; i <= cnt; ++i) {
        sort(g[i].begin(), g[i].end());
        g[i].erase( unique(g[i].begin(), g[i].end()) , g[i].end() );
        mul[i] = i;
        r[i] = 0;
    }

    //printGraph();

    int nrUnlock = 0;
     vector<int> change;

    for(int i = 1; i <= k ; ++i) {

        for(int x : change) {
            mul[x] = x;
            r[x] = 0;
        }

        change.clear();

        for(int x : color[i]) {//toate componentele atinse de o componenta a culorii i se unesc
                            //cu componenta x
            change.push_back(x);

            for(int y : g[x]) {

                int repr1 = find(y);
                change.push_back(y);

                int repr2 = find(x);
                unite(repr1, repr2);
            }
        }

        int rep = find(color[0][0]);

        int ok = 1;

        for(int x : color[0]) {
        
            if(find(x) != rep){
                ok = 0;
                break;
            }
        }

        nrUnlock += ok;
    }

    fout << nrUnlock << '\n'; 

    reset();
}
 
 
int main() {
 
     
    int t;
 
    fin >> t;
 
    while(t--) {

        read();
 
        solve();
    }
 
    return 0;
}