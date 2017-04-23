#include <iostream>

using namespace std;


const int k = 6;
class dr {
public:
	int *l ;

	dr(int x){
		l = new int;
		*l = 7;
	}

	~dr() {

		delete l;
	}
};


int main() {

	dr x(4);

	
	cout << (*x.l);

	delete &x;
	//cout << (*x.l);
	return 0;
}