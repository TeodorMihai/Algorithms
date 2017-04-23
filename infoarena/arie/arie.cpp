#include <bits/stdc++.h>

using namespace std;
 
#define point pair <double, double>
#define x first
#define y second
 
ifstream fin ("arie.in");
ofstream fout ("arie.out");
 
const double eps = 0.0001;
const int NMAX = 25;
 
int N; point V[NMAX]; point cur[NMAX]; point old[NMAX]; int curCnt; int oldCnt; int M; point P[NMAX];
 
int read() {
 
    fin >> N;
    for(int i = 1; i <= N; ++i) {
 
        double a, b; fin >> a >> b;
        V[i] = make_pair(a, b);
    }
    V[N + 1] = V[1];
 
    fin >> M;
    for(int i = 1; i <= M; ++i){
        double a, b; fin >> a >> b;
        P[i] = make_pair(a, b);
    }
    P[1 + M] = P[1];
}
 
int sarrus(point A, point B, point C) {
 
    double a = A.y - B.y; double b = B.x - A.x; double c = A.x * B.y - A.y * B.x;
 
    if(a * C.x + b * C.y + c < eps)
        return -1;
    return 1;
}
 
double det(double A, double B, double C, double D) {
    return A * D - B * C;
}
 
point intersection(point A, point B, point C, point D) {
 
    double a1 = A.y - B.y; double b1 = B.x - A.x; double c1 = -A.x * B.y + A.y * B.x;
    double a2 = C.y - D.y; double b2 = D.x - C.x; double c2 = -C.x * D.y + C.y * D.x;
 
    double newX = det(c1, b1, c2, b2) / det(a1, b1, a2, b2);
    double newY = det(a1, c1, a2, c2) / det(a1, b1, a2, b2);
 
    return make_pair(newX, newY);
}
 
 
double getArea(int sgn) {
 
    oldCnt = N;
    for(int i = 1; i <= N + 1; ++i)
        old[i] = V[i];
 
    for(int i = 1; i <= M; ++i) {
        //iau fiecare dreapta
        curCnt = 0;
        for(int j = 1; j <= oldCnt; ++j) {
            //gasesc punctele din intorior si din intersectie
            //merge doar daca dreapta mea le separa corespunzator
 
            if(sarrus(P[i], P[i + 1], old[j]) == sgn){
                cur[++curCnt] = old[j];
                if(sarrus(P[i], P[i + 1], old[j + 1]) == -sgn)
                    cur[++curCnt] = intersection(P[i], P[i + 1], old[j] , old[j + 1]);
            } else if(sarrus(P[i], P[i + 1], old[j + 1]) == sgn)
                cur[++curCnt] = intersection(P[i], P[i + 1], old[j], old[j + 1]);
        }
 
        if(curCnt == 0) return 0;
        oldCnt = curCnt;
        for(int j = 1; j <= curCnt; ++j)
            old[j] = cur[j];
        old[curCnt + 1] = old[1];
    }
 
    double area = 0;

    for(int i = 1; i <= oldCnt; ++i)
        cout << old[i].x << ' ' << old[i].y << '\n'; 
 
    for(int i = 1; i <= oldCnt; ++i)
        area += det(old[i].x, old[i].y, old[i + 1].x, old[i + 1].y);
    if(area < 0) area = -area;
 
    return area * 0.5;
}
 
int main() {
 
    read();
 
    fout << fixed;
    fout << setprecision(3) << max(getArea(1), getArea(-1));
 
    return 0;
}