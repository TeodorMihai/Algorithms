#include <bits/stdc++.h>

using namespace std;


class Hasher {

public:
	size_t operator()(const pair<int, int>& p) const {

		return p.first %  1232432;
	}
};


int main() {

	/*
	unordered_multiset< pair<int, int> , Hasher> ms;

	ms.insert({2, 4});
	ms.insert({2, 6});

	cout << ms.count({2, 4}) << '\n';
	*/
	//unique keys ie string
	unordered_multimap<string, int> um;

	um.insert({"ana", 2});
	um.insert({"ana", 5});
	//um.erase("ana");
	cout << um.count("ana") << '\n';

	auto range = um.equal_range("ana");

	for(auto p = range.first ; p != range.second; ++p)
			cout << p->second << '\n';


	for(auto& x : um)
		cout << x.first << ' ' << x.second << '\n';
	return 0;
}