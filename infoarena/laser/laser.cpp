#include <bits/stdc++.h>

using namespace std;

ifstream fin("laser.in");
ofstream fout("laser.out");

const int NMAX = 520;
const double eps = 1e-5;

#define Point pair<double, double>

struct Segment {

	Point a;
	Point b;
	Segment(double x1, double y1, double x2, double y2) {

		a.first = x1; a.second = y1;
		b.first = x2; b.second = y2;
	}
};

int n;//nr ecuatii aka neoane 
int m;//nr necunoscute, aka lasere

bool a[NMAX][NMAX * 2];
 //a[i][j] = 1 daca neonul i isi schimba starea prin aprinderea laserului j

bool sol[NMAX * 2];//starea unui laser

vector<Segment> seg;
vector<Point> points;
vector<double> lasers;

void read() {

	fin >> n;

	for(int i = 1; i <= n; ++i) {

		double x1, x2, y1, y2;
		fin >> x1 >> y1 >> x2 >> y2;
		seg.push_back({x1, y1, x2, y2});
		points.push_back({x1, y1});
		points.push_back({x2, y2});
	}
}


double getDegrees(Point p) {

	double d = atan2(p.second, p.first) * ( 180.0 / M_PI );

	if(d < 0.0) return d + 360.0;
	return d;
}

struct cmp {

	bool operator() (const Point& p1, const Point& p2) {


		double degu1 = getDegrees(p1);
		double degu2 = getDegrees(p2);

		return degu1 < degu2;
	}

} cmp1 ;

double modulo(double x) { return x > 0 ? x : -x; }

bool intersects(Point p1, Point p2, double degu3) {

	double degu1 = getDegrees(p1);
	double degu2 = getDegrees(p2);

	bool inter = (degu1 <= degu3 && degu3 <= degu2 ) ||
			(degu2 <= degu3 && degu3 <= degu1 );

	if(modulo(degu1 - degu2) < 180.0) 
		return inter;
			else 
		return !inter;

}

void constructMatrix() {

	for(int i = 1; i <= n ; ++i)
		fin >> a[i][m + 1];

	for(int i = 1; i <= n; ++i) {//segemnt aka ecuatie
		
		Segment s = seg[i - 1];
		for(int j = 1; j <= m ; ++j) {//laser aka necunoscuta
			//segemntul s intereseacteaza laserele cu unghiul: dat de punctul
			double p = lasers[j - 1];
			if(intersects(s.a, s.b, p))
				a[i][j] = true;

		}
	}
}

void gauss() {

	int i = 1; int j = 1;

	while(i <= n && j <= m) {

		//caut element nenul pe coloana j
		int x = i;
		for( ; x <= n ; ++x)
			if(a[x][j])
				break;
		if(x == n + 1) {//variabila libera
			sol[j] = false;
			j++;
			continue;
		}

		//interschimb linia i cu linia x
		for(int c = 1 ; c <= m + 1; c++)
			swap(a[i][c], a[x][c]);

		//fac zerouri sub linia i
		for(x = i + 1; x <= n ; ++x)
			if(a[x][j])
				for(int c = j ; c <= m + 1; c++)
					a[x][c] = a[x][c] xor a[i][c];
		i++; j++;
	}

	for(i = n; i ; --i) {

		for(j = 1; j <= m + 1; ++j) {

			if(a[i][j] == true) 
				break;
		}

		/*
		if(j == m + 1) {
			cout << "Imposibil\n";
			exit(0);
		}
		*/

		sol[j] = a[i][m + 1];

		for(int c = j + 1; c <= m ; ++c)
			sol[j] = sol[j] xor (sol[c] and a[i][c]);	
	}
}


void solve() {

	sort(points.begin(), points.end(), cmp1);
	points.push_back(points[0]);

	for(int i = 0 ; i < points.size() - 1; ++i) {
		lasers.push_back(
			(getDegrees(points[i - 1]) + getDegrees(points[i])) / 2.0);
	}

	m = lasers.size();

	constructMatrix();
	gauss();


	int cnt = 0;
	for(int i = 1; i <= m; ++i)
		if(sol[i])
			cnt++;

	fout << cnt << '\n'; 

	fout << fixed << setprecision(6) ;

	for(int i = 1; i <= m; ++i)
		if(sol[i])
			fout << lasers[i - 1] << '\n'; 
}

int main() {

	read();

	solve();

	return 0;
}