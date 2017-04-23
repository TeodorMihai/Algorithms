#include <bits/stdc++.h>

using namespace std;


class Poly {

protected: 
	int x, y;
public:
	int area() { return x * y; }
	Poly() { }
	Poly(int x, int y) {
		this->x = x;
		this->y = y;
	}

	virtual void smth() = 0;
};

class Triangle : public Poly {

public:

	Triangle() { }
	Triangle(int x, int y) {
		this->x = x;
		this->y = y;
	}

	void smth() {

		cout << "Triangle\n";
	}

};

class Rect : public Poly {

public:
	Rect() { }
	Rect(int x, int y) {
		this->x = x;
		this->y = y;
	}

	void smth() {

		cout << "Rectangle\n";
	}
};


int main() {

	Rect r(1, 2);
	Triangle t(2, 3);
	Poly* p1 = &r;
	Poly* p2 = &t;

	p1->smth();
	p2->smth();

	return 0;
}