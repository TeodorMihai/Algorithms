#include <bits/stdc++.h>

using namespace std;

int main() {

	vector<int> s;
	s.push_back(2);
	s.push_back(3);
	s.clear();
	s.push_back(6);

	int i = 0;
	//for(set<int>::iterator it = s.begin(); it != s.end(); ++it, i++)
	//	if(i == 0)
	s.insert( s.begin() + 1, 1);
	s.insert( s.begin() + 2, 100);


	for(auto x : s)
		cout << x << '\n'; 

	return 0;
}