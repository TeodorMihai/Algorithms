#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("poligon.in");
ofstream fout("poligon.out");
 
typedef long long in64;

#define point pair<int, int>
#define pointd pair<double, double>
#define x first
#define y second
 
const int NMAX = 807;//nr vf-uri poligon
const int MMAX = 60009; //nr puncte
const int INF = 60009;
 
int n; int m;
 
point pol[NMAX];
point v[MMAX];

//coeficientii dreptelor segmentelor
in64 as[NMAX];
in64 bs[NMAX];
in64 cs[NMAX];
 
struct Segment {
 
    int ind;//indicele segmentului din poligon
    double middle;//punctul din mijlocul sectorului intersectat c poligonul

    Segment(int _ind, double _middle) : ind(_ind), middle(_middle) { }
};

struct cmp {

	bool operator()(const Segment& s1, const Segment& s2) {
		return s1.middle < s2.middle;
	}
} cmpMiddle;
 
struct Sector {
 
    int inf; int sup;
    vector<Segment> seg;
};
 
Sector s[NMAX]; int cnt;
 
int f[INF];
 
void read() {
 
    fin >> n >> m;
    for(int i = 1; i <= n; ++i)
        fin >> pol[i].x >> pol[i].y;
 
    for(int i = 1; i <= m ; ++i)
        fin >> v[i].x >> v[i].y;
}


int findSector(point p) {
 
    int pos = 0 ; int step ;
    for( step = 1; step <= cnt; step <<= 1);
 
    for(pos = 0; step ; step >>= 1)
        if(pos + step < cnt && s[pos + step].sup < p.x)
            pos += step;
 
    return pos + 1;
}

int sgn(Segment seg, point p) {

	int ind = seg.ind;
	in64 po = as[ind] * p.x + bs[ind] * p.y + cs[ind];
	
	if(po == 0ll)//pe segment
		return 0;
	else if(po > 0)
		return 1;
	else return -1;
}


int count(const Sector& sector, point p) {
 	
	if(sector.seg.size() == 0)//clar pe dinafara
		return 0;

    int pos; int step;

    for(step = 1; step < sector.seg.size(); step <<= 1);
 
    for(pos = 0; step ; step >>= 1)
        if(pos + step < sector.seg.size() 
            && sgn(sector.seg[pos + step], p) == 1)
            pos += step;

    //pos == cate segmente sunt strict sub punctul meu
    if(pos + 1 < sector.seg.size() && sgn(sector.seg[pos + 1], p) == 0)
    	return 1; //daca e pe vreo muchie (==0) trebuie luat, returnez orice nr impar

 	if(pos == 0 && sgn(sector.seg[0], p) == -1)
 		return 0;

    return pos + 1;
}


double intersection(int coordx, in64 a, in64 b, in64 c) {
 	//b nu poate fi 0
    return 1.0 * (-c - a * coordx) / b;
}
 
void solve() {

    for(int i = 1 ; i <= n; ++i)
        f[pol[i].x] = 1;
 
    int start;
 
    if(f[0] == 1)
        start = 0;
    else {
        start = 1;
        s[++cnt].inf = 0;
    }
 
    for(int i = start ; i < INF; ++i)
        if(f[i])
            s[++cnt].inf = i;
 
    for(int i = 1; i < cnt; ++i)
        s[i].sup = s[i + 1].inf;
 
    s[cnt].sup = INF;
 
 
    pol[n + 1] = pol[1];

    for(int j = 1; j <= n; ++j) {
    	as[j] = 1ll * pol[j].y - pol[j + 1].y;
        bs[j] = 1ll * pol[j + 1].x - pol[j].x;
        cs[j] = 1ll * pol[j].x * pol[j + 1].y - pol[j].y * pol[j + 1].x;

        if(bs[j] < 0) //vrem inegalitatea (punct sub / deasupra unui segment) relativ la axa oy
        	as[j] *= -1, bs[j] *= -1, cs[j] *= -1;
    }
 
    for(int i = 1; i <= cnt; ++i) {
        //fiecare sector
        for(int j = 1; j <= n ; ++j) { //segment, j -> j + 1
 
            if( (pol[j].x <= s[i].inf && s[i].sup <= pol[j + 1].x) ||
                (pol[j + 1].x <= s[i].inf && s[i].sup <= pol[j].x) ) {

 
                double y1 = intersection(s[i].inf, as[j], bs[j], cs[j]);
                double y2 = intersection(s[i].sup, as[j], bs[j], cs[j]);
              
                s[i].seg.push_back(Segment(j, (y1 + y2) * 0.5 ));
            }
        }
 
        sort(s[i].seg.begin(), s[i].seg.end(), cmpMiddle);
    }
 	
    int nrPoints = 0;
    for(int i = 1; i <= m; ++i) {
 
        int sec = findSector(v[i]);
        if(count(s[sec], v[i]) % 2) 
            nrPoints++;
    }
 
    fout << nrPoints << '\n';
}
 
int main() {
 
    read(); solve();
    return 0;
}