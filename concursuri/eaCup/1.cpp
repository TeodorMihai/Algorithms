#include <bits/stdc++.h>

using namespace std;



int solution(int X, vector<int> &A) {
    // write your code in C++11
	//new meaning for A[i], how many elemnts in [0..i] are equal with X
	A[0] = (A[0] == X);

	for(unsigned i = 1 ; i < A.size(); ++i) {

		A[i] = A[i - 1] + (A[i] == X);

	}

	if(A[A.size() - 1] == A.size())
		return 0;

	for(unsigned i = 0 ; i < A.size(); ++i)

		if(A[i] == (A.size() - (i + 1)) - (A[A.size() - 1] - A[i]) )
			return i + 1;
}


int main() {

	vector<int> v;
	int X;
	int N;

	cin >> N >> X;

	for(int i = 0 ; i < N; ++i) {

		int z;
		cin >> z;

		v.push_back(z);
	}

	cout << solution(X, v) << '\n';
}