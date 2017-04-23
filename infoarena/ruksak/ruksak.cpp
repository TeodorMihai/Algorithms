#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300009;
const int MAXG = 3005;

ifstream fin("ruksak.in");
ofstream fout("ruksak.out");

int n; int g;

struct Obj {
    int w; int p;
};

vector<int> improved;
vector<int> newImproved;

Obj obj[MAXN];

int profMax = 0;
int s[MAXG];
 
void read()  {
    fin >> n >> g;
    for(int i = 1;i <= n;i++) 
        fin >> obj[i].w >> obj[i].p;
}

bool cmp(const Obj& ob1, const Obj& ob2) {

    if(ob1.w == ob2.w)
        return ob1.p > ob2.p;
    return ob1.w < ob2.w;
}


 
void solve() {

    sort(obj + 1, obj + 1 + n, cmp);

    improved.push_back(0);

    for(int i = 1; i <= n; i++) {

        int w = obj[i].w;
        int p = obj[i].p;

        if(i != 1 && obj[i].w != obj[i - 1].w) {
            improved.clear();
            for(int k = g ; k >= 0 ; --k) 
                improved.push_back(k);
        }

        for(unsigned int t = 0; t < improved.size() ; ++t) {

            int j = improved[t];
       
            if(j + w <= g && s[j] + p > s[j + w]) {

                s[j + w] = s[j] + p;
                newImproved.push_back(j + w);
                  
                if(s[j + w] > profMax)
                    profMax = s[j + w]; 
            }
        }

        improved = newImproved;
        newImproved.clear();
    } 

}
 
int main() {
 
    read();
    solve();

    fout << profMax << '\n'; 
    return 0;
}