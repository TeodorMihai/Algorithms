#include <bits/stdc++.h>

using namespace std;

class Poli;


class Anim { 

private:

	int t;
public:

	int re;
	int im;
	int* mem;
	Anim() { 

		mem = new int[100];

		re = 2;
		im = 3;
		
	}


	~Anim() { 

		//cout << "Free\n" ;
		delete[] mem;
	}


	Anim(const Anim& a) {
		//cout << "Apelare\n";
		this->mem = new int[100];
		memcpy(this->mem, a.mem, 100 * sizeof(int));
		this->re = a.re;
		this->im = a.im;
	}

	int* getMem() {

		return mem;
	}

	int& getRe() {

		return re;
	}
	

	//o functie cu 2 argumente, unul this, altul other: this = other
	//friend Anim& operator= (const Anim& other);

	Anim& operator= (const Anim& other) {
	//	cout << "Operatorul egal\n";
		memcpy(mem, other.mem, sizeof(int) * 100);
		this->re = other.re;
		this->im = other.im;

		return* this;
	}

	friend class Poli;
	
	friend Anim operator+ (const Anim& fs, const Anim& sd);

	friend istream& operator>> (istream& in, Anim& a);
	friend ostream& operator<< (ostream& out, const Anim& a);
	
	bool operator() (const Anim& sd) const {
		cout << "Apelare () const \n";
		return (this->re == sd.re) ? (this->im < sd.im) : (this->re < sd.re);
	}


	bool operator() (const Anim& sd) {
		cout << "Apelare ()xx\n";
		return (this->re == sd.re) ? (this->im < sd.im) : (this->re < sd.re);
	}


	operator int() {

		cout << "apelare static cast\n";
		return re;
	}

	operator int() const {
		return re;
	}
};



Anim operator+ (const Anim& fs, const Anim& sd) {

	Anim a;
	a.re = fs.re + sd.re;
	a.im = fs.im + sd.im;
	return a;
}

istream& operator>> (istream& in, Anim& a) {

	in >> a.re >> a.im;
	return in;
}

ostream& operator<< (ostream& out, const Anim& a) {

	out << '(' << a.re << ',' << a.im << ")\n";
	return out;
}



class Poli {

public:
	void fun(Anim a) {

		a.t = 1;
	}

};


Anim f(Anim b) {

	return b;
}


void fff(int x) {


}


int main() {

	Anim a;
	f(a);
	Anim b = Anim(a);
	b = a;

	a.getMem()[2] = 2;
	*(a.getMem() + 4) = 6;
	//cout << a.mem[4] << '\n';

	Poli p;
	p.fun(a);

	Anim x1;
	Anim x2;
	Anim x3 = x1 + x2;
	const Anim x4;
	cout << x3 << x1 << '\n';
	cout << x3(x1) << '\n';
	cout << x4(x2) << '\n';

	int* pp = new int;
	*pp = 5;

	x1.getRe() = 99;
	cout << x1.re << '\n';

	fff(x1);

	int t = static_cast<int>(x1);
	cout << t << '\n';
	return 0;

}

