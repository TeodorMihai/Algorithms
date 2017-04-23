#include <fstream>
#include <iostream>

using namespace std;

const int NMAX = 10000;



//v[i][j]  -combinari de i luate cate j - 1

int comb(int n, int k) {


	if(n == 0 || n < 0 || k < 0 || k > n)
		return -1;

	int* v = NULL;
	int* vOld = NULL;

	k = min(n - k, k);

	v = new int[k + 2]();
	vOld = new int[k + 2]();


	vOld[0] = 0;
	vOld[1] = vOld[2] = 1;

	if(n == 1) return 1;
	if(k == 0 || k == n) return 1;
	if(k == 1) return n;


	for(int i = 1 ; i <= n - 1; ++i) {


		for(int j = 1 ; j <= min(k + 1, i + 2) ; ++j)
			v[j] = vOld[j] + vOld[j - 1];

			

		swap(v, vOld);

		if(vOld[k + 1] > 1000000000)
			return -1;
	}

	return vOld[k + 1];


}

int main() {

	int n; int k;

	cin >> n >> k;
	cout << comb(n, k) << '\n'; 

	return 0;
}