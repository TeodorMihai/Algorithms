#include <bits/stdc++.h>

using namespace std;


struct filter5 {

	bool operator() (int x) {
		return x <= 5;
	}

} flt5;

int main() {

	vector<int> v = { 5, 2, 6, 2, 5, 7, 8, 2, 4, 6};

	sort(v.begin(), v.end(), [] (const int& a, const int& b) -> bool {
		return a < b;
	});

	for(auto x : v)
		cout << x << ' ';
	cout << '\n'; 

	//returneaza primul element

	cout << *find_if(v.begin(), v.end(), flt5) << '\n'; //returns an iterator

	//filter
	vector<int> afterFilter(v.size());

	auto it = copy_if( v.begin(), v.end(), afterFilter.begin(), [ ] (int x) -> bool {
		return x <= 5;
	});

	//sau clasic 

	//auto it = copy_if( v.begin(), v.end(), afterFilter.begin(), flt5);

	afterFilter.resize(distance(afterFilter.begin(), it));


	for(auto x : afterFilter)
		cout << x << ' ';
	cout << '\n'; 
	return 0;
}