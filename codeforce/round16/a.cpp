#include <bits/stdc++.h>

using namespace std;


char s[2];

int main() {

	cin >> s;

	if(s[0] == 'a' || s[0] ==  'h') {
		if(s[1] == '1' || s[1] == '8') 
			cout << 3 << '\n';
		else 
			cout << 5 << '\n';
	} else if(s[1] == '1' || s[1] == '8')	
			cout << 5 << '\n';
		else 
			cout << 8 << '\n';

	return 0;
}