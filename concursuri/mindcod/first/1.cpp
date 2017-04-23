#include <bits/stdc++.h>

using namespace std;

int main() {

	double t1, k1, t2, k2;

	double d = 1e12;
	cin >> t1 >> k1 >> t2 >> k2;
	double t11 = (t1 / k1);
	double t22 = (t2 / k2);

	double v1 = d / t11;
	double v2 = (d / t22);
	double res = d / (v1 + v2);
	cout << fixed;
	cout << setprecision(5) << res << '\n';
	return 0;
}